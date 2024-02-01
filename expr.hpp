//
//  expr.hpp
//  expressionclass
//
//  Created by Koffi Danhounsrou on 1/16/24.
//

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>
#include <iostream>

//
//  Expr.cpp
//  expressionclass
//
//  Created by Koffi Danhounsrou on 1/16/24.
//

//
class Expr{
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable() = 0 ;
    virtual Expr* subst(const std::string& variable, Expr* replacement) = 0;
};
//
class Num : public Expr{
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string& variable, Expr* replacement);
};
//
class Add : public Expr{
    public:
    Expr *lhs;
    Expr *rhs;
    Add(Expr *lhs, Expr *rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string& variable, Expr* replacement);
};
//
class Mult : public Expr{
    
public:
    Expr *lhs;
    Expr *rhs;
    Mult(Expr *lhs, Expr *rhs){
        this->lhs = lhs;
        this->rhs = rhs;
    }
    bool equals(Expr *e);
    int interp();
    bool has_variable();
    Expr* subst(const std::string& variable, Expr* replacement);
};

class Var : public Expr{

public:
    std::string name;
    Var(const std::string& name);
    int interp() ;
    bool has_variable();
    bool equals(Expr *e) ;
    Expr* subst(const std::string& variable, Expr* replacement);
};




#endif /* expr_hpp */
