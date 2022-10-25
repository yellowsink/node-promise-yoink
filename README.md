# Node promise yoink

Works like bun.peek().

Originally I was gonna do this via a native module and NAPI villainy.

Now i just abuse _tickCallback :(

thanks kyza for the easy way.

An extract of the original code:
```c
// this is the worst decision i will ever make
#include <v8/include/v8-promise.h>

static napi_value Yoink(napi_env env, napi_callback_info info) 
{
  napi_status status;

  size_t argcount = 1;
  napi_value args[1];
  
  status = napi_get_cb_info(env, info, &argcount, args, NULL, NULL);
  assert(status == napi_ok);

  if (argcount != 1)
  {
    napi_throw_type_error(env, NULL, "Wrong number of arguments!");
    return NULL;
  }
  
  bool isPromise;
  status = napi_is_promise(env, args[0], &isPromise);
  assert(status == napi_ok);

  if (!isPromise)
    return args[0]; // lol

  // i wonder what would happen if i-
  Promise uhhh = args[0];

  return NULL;
}
```