// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <cxxReactABI16_0_0/ABI16_0_0CxxModule.h>
#include <cxxReactABI16_0_0/ABI16_0_0NativeModule.h>

namespace facebook {
namespace ReactABI16_0_0 {

class Instance;

std::function<void(folly::dynamic)> makeCallback(
  std::weak_ptr<Instance> instance, ExecutorToken token, const folly::dynamic& callbackId);

class CxxNativeModule : public NativeModule {
public:
  CxxNativeModule(std::weak_ptr<Instance> instance,
                  std::unique_ptr<xplat::module::CxxModule> module);

  std::string getName() override;
  std::vector<MethodDescriptor> getMethods() override;
  folly::dynamic getConstants() override;
  bool supportsWebWorkers() override;
  void invoke(ExecutorToken token, unsigned int ReactABI16_0_0MethodId, folly::dynamic&& params) override;
  MethodCallResult callSerializableNativeHook(
    ExecutorToken token, unsigned int hookId, folly::dynamic&& args) override;

private:
  std::weak_ptr<Instance> instance_;
  std::unique_ptr<xplat::module::CxxModule> module_;
  std::vector<xplat::module::CxxModule::Method> methods_;
};

}
}