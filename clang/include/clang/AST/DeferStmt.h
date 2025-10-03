#ifndef LLVM_CLANG_AST_DEFERSTMT_H
#define LLVM_CLANG_AST_DEFERSTMT_H

#include "clang/AST/Stmt.h"

namespace clang {

class DeferStmt final : public Stmt {
  SourceLocation DeferLoc;
  Stmt *Body;

public:
  DeferStmt(SourceLocation Dl, Stmt *Body)
      : Stmt(DeferStmtClass), DeferLoc(Dl), Body(Body) {}

  explicit DeferStmt(EmptyShell Empty) : Stmt(DeferStmtClass, Empty) {}

  const Stmt *getBody() const { return Body; }
  void setDeferLoc(SourceLocation L) { DeferLoc = L; }
  void setBody(Stmt *S) { Body = S; }
  Stmt *getBody() { return Body; }

  SourceLocation getDeferLoc() const { return DeferLoc; }

  static bool classof(const Stmt *T) {
    return T->getStmtClass() == Stmt::DeferStmtClass;
  }

  child_range children() { return child_range(&Body, &Body + 1); }
  const_child_range children() const {
    return const_child_range(const_cast<Stmt**>(&Body), const_cast<Stmt**>(&Body + 1));
  }

  SourceLocation getBeginLoc() const { return DeferLoc; }
  SourceLocation getEndLoc() const {
    if (Body)
      return Body->getEndLoc();
    return DeferLoc;
  }

  SourceRange getSourceRange() const {
    return SourceRange(getBeginLoc(), getEndLoc());
  }
};

} // namespace clang

#endif // LLVM_CLANG_AST_DEFERSTMT_H
