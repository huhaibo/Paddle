/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "paddle/operators/add_op.h"

namespace paddle {
namespace operators {

class AddOp : public OperatorWithKernel {
 protected:
  void InferShape(const InferShapeContext &ctx) const override {
    PADDLE_ENFORCE_EQ(ctx.Input<Tensor>("X")->dims(),
                      ctx.Input<Tensor>("Y")->dims(),
                      "Two input of Add Op's dimension must be same.");
    ctx.Output<Tensor>("Out")->Resize(ctx.Input<Tensor>("X")->dims());
  }
};

class AddOpMaker : public OpProtoAndCheckerMaker {
 public:
  AddOpMaker(OpProto *proto, OpAttrChecker *op_checker)
      : OpProtoAndCheckerMaker(proto, op_checker) {
    AddInput("X", "The first input of add op");
    AddInput("Y", "The second input of add op");
    AddOutput("Out", "The output of add op");
    AddComment(R"DOC(
Two Element Add Operator.

The equation is: Out = X + Y
)DOC");
  }
};

class AddOpGrad : public OperatorWithKernel {
 protected:
  void InferShape(const InferShapeContext &ctx) const override {}
};

}  // namespace operators
}  // namespace paddle

REGISTER_OP(add_two, ops::AddOp, ops::AddOpMaker);
REGISTER_GRADIENT_OP(add_two, add_two_grad, ops::AddOpGrad);
REGISTER_OP_CPU_KERNEL(add_two, ops::AddKernel<ops::CPUPlace, float>);
