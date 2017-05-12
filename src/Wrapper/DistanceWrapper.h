#ifndef DISTANCEWRAPPER_H
#define DISTANCEWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../Modules/Distance/DistanceSensor.h"

class DistanceWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit DistanceWrapper(uint8_t _header);
  ~DistanceWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getBasicValue(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  DistanceSensor *distance;
};

#endif
