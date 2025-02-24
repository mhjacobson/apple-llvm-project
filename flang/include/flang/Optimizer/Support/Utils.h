//===-- Optimizer/Support/Utils.h -------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Coding style: https://mlir.llvm.org/getting_started/DeveloperGuide/
//
//===----------------------------------------------------------------------===//

#ifndef FORTRAN_OPTIMIZER_SUPPORT_UTILS_H
#define FORTRAN_OPTIMIZER_SUPPORT_UTILS_H

#include "flang/Common/default-kinds.h"
#include "flang/Optimizer/Dialect/FIRType.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringRef.h"

namespace fir {
/// Return the integer value of a arith::ConstantOp.
inline std::int64_t toInt(mlir::arith::ConstantOp cop) {
  return cop.getValue().cast<mlir::IntegerAttr>().getValue().getSExtValue();
}

// Reconstruct binding tables for dynamic dispatch.
using BindingTable = llvm::DenseMap<llvm::StringRef, unsigned>;
using BindingTables = llvm::DenseMap<llvm::StringRef, BindingTable>;
void buildBindingTables(BindingTables &, mlir::ModuleOp mod);

// Translate front-end KINDs for use in the IR and code gen.
inline std::vector<fir::KindTy>
fromDefaultKinds(const Fortran::common::IntrinsicTypeDefaultKinds &defKinds) {
  return {static_cast<fir::KindTy>(defKinds.GetDefaultKind(
              Fortran::common::TypeCategory::Character)),
          static_cast<fir::KindTy>(
              defKinds.GetDefaultKind(Fortran::common::TypeCategory::Complex)),
          static_cast<fir::KindTy>(defKinds.doublePrecisionKind()),
          static_cast<fir::KindTy>(
              defKinds.GetDefaultKind(Fortran::common::TypeCategory::Integer)),
          static_cast<fir::KindTy>(
              defKinds.GetDefaultKind(Fortran::common::TypeCategory::Logical)),
          static_cast<fir::KindTy>(
              defKinds.GetDefaultKind(Fortran::common::TypeCategory::Real))};
}
} // namespace fir

#endif // FORTRAN_OPTIMIZER_SUPPORT_UTILS_H
