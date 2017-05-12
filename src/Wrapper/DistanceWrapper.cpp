#include <node.h>
#include "DistanceWrapper.h"

using namespace v8;

Persistent<Function> DistanceWrapper::constructor;

DistanceWrapper::DistanceWrapper(uint8_t _header){
  distance = new DistanceSensor(_header);
}

DistanceWrapper::~DistanceWrapper(){
  // delete distance;
}

void DistanceWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  DistanceWrapper* temp_obj = ObjectWrap::Unwrap<DistanceWrapper>(args.Holder());
  temp_obj->distance->release();
  delete temp_obj->distance;
}

void DistanceWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"DistanceWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"getValue",getValue);
  NODE_SET_PROTOTYPE_METHOD(tpl,"getBasicValue",getBasicValue);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"BCMEnd",BCMEnd);
  // tpl->PrototypeTemplate()->Set(Nan::New("temperature").ToLocalChecked(),
  //   Nan::New<v8::FunctionTemplate>(Temperature)->GetFunction());

  constructor.Reset(isolate,tpl->GetFunction());
}

void DistanceWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _header = 0x01;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  DistanceWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 1:
        _header = (uint8_t) args[0]->NumberValue();
        obj = new DistanceWrapper(_header);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      default:
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc > 1){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void DistanceWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc > 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void DistanceWrapper::getValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  DistanceWrapper* temp_obj = ObjectWrap::Unwrap<DistanceWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->distance->getValue()));
}

void DistanceWrapper::getBasicValue(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  DistanceWrapper* temp_obj = ObjectWrap::Unwrap<DistanceWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->distance->getBasicValue()));
}
// void Temperature(){
//   OpticalDistanceSensor temp;
//   temp.selectPort(3);
//   printf("Temp Input: %0.2f\n",temp.getTemperature());
// }
