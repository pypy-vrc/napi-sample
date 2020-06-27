#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>
#include <js_native_api.h>

napi_value sample(napi_env env, napi_callback_info info)
{
    napi_value result;

    printf("sample called\n");

    napi_create_string_utf8(env, "ok", NAPI_AUTO_LENGTH, &result);

    return result;
}

napi_value sum(napi_env env, napi_callback_info info)
{
    double sum, value;
    size_t argc;
    napi_value *argv;
    napi_value result;

    sum = 0;

    napi_get_cb_info(env, info, &argc, NULL, NULL, NULL);
    if (argc > 0)
    {
        argv = (napi_value *)malloc(sizeof(napi_value) * argc);
        napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
        for (size_t i = 0; i < argc; ++i)
        {
            if (napi_get_value_double(env, argv[i], &value) == napi_ok)
            {
                sum += value;
            }
        }
        free(argv);
    }

    napi_create_double(env, sum, &result);

    return result;
}

NAPI_MODULE_INIT()
{
    napi_value value;

    napi_create_function(env, NULL, 0, sample, NULL, &value);
    napi_set_named_property(env, exports, "sample", value);

    napi_create_function(env, NULL, 0, sum, NULL, &value);
    napi_set_named_property(env, exports, "sum", value);

    return exports;
}
