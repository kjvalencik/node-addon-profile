#include <stddef.h>
#include <stdio.h>

#define SIZE_MAX ((size_t)-1)
#define NAPI_AUTO_LENGTH SIZE_MAX

typedef int napi_status;

typedef void* napi_value;
typedef void* napi_env;
typedef void* napi_callback_info;

typedef napi_value (*napi_callback)(napi_env, napi_callback_info);

napi_status napi_create_function(
	napi_env env,
	const char* utf8name,
	size_t length,
	napi_callback cb,
	void* data,
	napi_value* result
);

napi_status napi_set_named_property(
	napi_env env,
	napi_value object,
	const char* utf8Name,
	napi_value value
);

napi_value busy_loop(napi_env _env, napi_callback_info _info) {
	printf("busy loop called\n");

	for (int i = 0; i < 1e9; i++) {}

	return 0;
}

napi_value noop(napi_env _env, napi_callback_info _info) {
	printf("noop called\n");
	return 0;
}

napi_value napi_register_module_v1(napi_env env, napi_value m) {
	napi_value result;
	napi_status status;

	status = napi_create_function(env, "busyLoop", NAPI_AUTO_LENGTH, busy_loop, NULL, &result);
	if (status != 0) {
		printf("failed to create busyLoop\n");
		return m;
	}

	status = napi_set_named_property(env, m, "busyLoop", result);
	if (status != 0) {
		printf("failed to export busyLoop\n");
		return m;
	}

	status = napi_create_function(env, "noop", NAPI_AUTO_LENGTH, noop, NULL, &result);
	if (status != 0) {
		printf("failed to create noop\n");
		return m;
	}

	status = napi_set_named_property(env, m, "noop", result);
	if (status != 0) {
		printf("failed to export noop\n");
		return m;
	}

    return m;
}
