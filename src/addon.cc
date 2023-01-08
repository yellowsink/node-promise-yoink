#include <node_api.h>
#include <stdio.h>
#include <assert.h>
#include "../v8/include/v8-promise.h"

// EWWWW
#include <iostream>

#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

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

  // goofy ahh
  auto promise = *((v8::Object*) (void*) args[0]);

  std::cout << "here 1!" << std::endl;
  std::cout << promise.IsValue() << std::endl;
  auto ctxt = promise.GetCreationContextChecked();
  
  std::cout << "here 2!" << std::endl;
  //auto detail = promise.ToDetailString(ctxt);
  //return *((napi_value*) (void*) &detail);
  return NULL;
}

NAPI_MODULE_INIT() {
  napi_status status;
  napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("yoink", Yoink);
  status = napi_define_properties(env, exports, 1, &addDescriptor);
  assert(status == napi_ok);
  return exports;
}