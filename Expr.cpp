//
//  Expr.cpp
//  expressionclass
//
//  Created by Koffi Danhounsrou on 1/16/24.
//

#include "expr.hpp"
#include <iostream>
#include "catch.h"
using namespace std;

//------------------NUM IMPLEMENTATION----------------//
//NUM::NUM
Num::Num(int val){
    this->val = val;
}
//NUM::EQUALS
bool Num::equals(Expr *exp){
    Num *expVal = dynamic_cast<Num*>(exp);
    
        // Check if dynamic_cast was successful
    if (expVal) {
        return expVal->val == this->val;
    }
    return false;
}
//NUM::INTERP
int Num::interp(){
    return this->val;
}
//NUM::HAS_VARIABLE
bool Num::has_variable(){
    return false;
}
//NUM::SUBST
Expr* Num::subst(const std::string& variable, Expr* replacement)  {
      return this;
  }

//------------_ADD IMPLEMENTATION------------------//
//ADD::EQUALS
bool Add::equals(Expr *exp){
    Add *addExp = dynamic_cast<Add*>(exp);
    
        // Check if dynamic_cast was successful
    if (addExp) {
        return addExp->lhs->equals(this->lhs) && addExp->rhs->equals(this->rhs);
    }
    return false;
}
//ADD::INTERP
int Add::interp(){
    return this->lhs->interp() + this->rhs->interp();
}
//ADD::HAS_VARIABLE
bool Add::has_variable(){
        return lhs->has_variable() || rhs->has_variable();
  
}
//ADD::SUBST
Expr* Add::subst(const std::string& variable, Expr* replacement)  {
      return new Add(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
  }

//------------MULT IMPLEMENTATION------------------------//
//MULT::EQUALS
bool Mult::equals(Expr *exp){
    Mult *multExp = dynamic_cast<Mult*>(exp);
    
    // Check if dynamic_cast was successful
    if (multExp) {
        return multExp->lhs->equals(this->lhs) && multExp->rhs->equals(this->rhs);
    }
    return false;
}
//MULT::INTERP
int Mult::interp(){
    return this->lhs->interp() * this->rhs->interp();
}
//MULT::HAS_VARIABLE
bool Mult::has_variable(){
    return lhs->has_variable() || rhs->has_variable();

}
//Mult::SUBST
Expr* Mult::subst(const std::string& variable, Expr* replacement) {
      return new Mult(lhs->subst(variable, replacement), rhs->subst(variable, replacement));
  }

//-------------VAR IMPLEMENTATION-----------------------------//
//VAR::VAR
Var::Var(const std::string& name) : name(name){};
//VAR::INTERP
int Var::interp()  {
    throw std::runtime_error("No value for variable!");
}
//VAR::HAS_VARIABLE
bool Var::has_variable(){
    return true;
}
//VAR::EQUALS
bool Var::equals(Expr* e) {
     Var* var = dynamic_cast<Var*>(e);
     if (var) {
         return var->name == this->name;
     }
     return false;
 }
//VAR::SUBST
Expr* Var::subst(const std::string& variable, Expr* replacement) {
    if (name == variable) {
        // Replace the variable with the provided replacement
        return replacement;
    } else {
        // No substitution needed for other variables
        return this;
    }
}

//-----------------------TESTCASES----------------------------------//
//Todo Test variable class---> 
//CHECK(num1->val == 10);
TEST_CASE("ARITHMETIC NUM"){
    Num * num1 = new Num(10);
    Expr * num2 = new Num(16);
    Num * num3 = new Num(15);
    Num * num4 = new Num(10);
    Expr * num5 = new Num(20);
    CHECK(num1->equals(num2) == 0);
  
    CHECK(num1->equals(num3) == 0);
    CHECK(num1->equals(num4) == 1);
    CHECK(num1->equals(num5) == 0);
    CHECK(num3->equals(num5) == 0);
    CHECK(num3->equals(num3) == 1);
}
TEST_CASE("ARITHMETIC ADD"){
    Expr *addExpr1 = new Add(new Num(5), new Num(7));
    Expr *addExpr2 = new Add(new Num(5), new Num(7));
    Expr *addExpr3 = new Add(new Num(7), new Num(7));
    Expr *addExpr4 = new Add(new Num(5), new Num(5));
    
    CHECK(addExpr1->equals(addExpr2) == 1);
    CHECK(addExpr1->equals(addExpr3) == 0);
    CHECK(addExpr2->equals(addExpr3) == 0);
    CHECK(addExpr3->equals(addExpr1) == 0);
    CHECK(addExpr4->equals(addExpr4) == 1);
}

TEST_CASE("ARITHMETIC MULT"){
    Expr *multExpr1 = new Mult(new Num(3), new Num(4));
    Expr *multExpr2 = new Mult(new Num(3), new Num(4));
    Expr *multExpr3 = new Mult(new Num(5), new Num(5));
    Expr *multExpr4 = new Mult(new Num(6), new Num(5));
    
    CHECK(multExpr1->equals(multExpr2) == 1);
    CHECK(multExpr2->equals(multExpr1) == 1);
    CHECK(multExpr1->equals(multExpr3) == 0);
    CHECK(multExpr2->equals(multExpr4) == 0);
    CHECK(multExpr4->equals(multExpr4) == 1);
}

TEST_CASE("ARITHMETIC NUM INTERP"){
 
    CHECK((new Num(20))->interp() == 20);
    CHECK((new Num(25))->interp() == 25);
    CHECK((new Num(26))->interp() == 26);
   
}

TEST_CASE("ARITHMETIC ADD INTERP"){
 
   
    CHECK( (new Add(new Add(new Num(10), new Num(15)),new Add(new Num(20),new Num(20))))
            ->interp()==65);
    CHECK( (new Add(new Add(new Num(20), new Num(25)),new Add(new Num(30),new Num(30))))
            ->interp()==105);
    CHECK( (new Add(new Add(new Num(20), new Num(20)),new Add(new Num(20),new Num(20))))
            ->interp()==80);
}

TEST_CASE("ARITHMETIC MULT INTERP"){
 
    CHECK( (new Mult(new Num(3), new Num(2)))
            ->interp()==6 );
    CHECK( (new Mult(new Num(5), new Num(2)))
            ->interp()==10 );
    CHECK( (new Mult(new Num(10), new Num(2)))
            ->interp()==20 );
}

// Test cases for has_variable
TEST_CASE("HAS VARIABLE NUM") {
    Num* num1 = new Num(10);
    CHECK(num1->has_variable() == false);
    Num* num2 = new Num(15);
    CHECK(num2->has_variable() == false);
    Num* num3 = new Num(30);
    CHECK(num3->has_variable() == false);
}

TEST_CASE("HAS VARIABLE ADD") {
    Expr* addExpr1 = new Add(new Num(5), new Num(7));
    CHECK(addExpr1->has_variable() == false);
    
    Expr* addExpr2 = new Add(new Num(5), new Var("x"));
    CHECK(addExpr2->has_variable() == true);
    
    Expr* addExpr3 = new Add(new Num(10), new Var("x"));
    CHECK(addExpr3->has_variable() == true);
    
    Expr* addExpr4 = new Add(new Num(10), new Num(10));
    CHECK(addExpr4->has_variable() == false);
    
    Expr* addExpr5 = new Add(new Mult(new Num(10), new Num(10)), new Num(10));
    CHECK(addExpr5->has_variable() == false);
}

TEST_CASE("HAS VARIABLE MULT") {
    Expr* multExpr1 = new Mult(new Num(3), new Num(4));
    CHECK(multExpr1->has_variable() == false);

    Expr* multExpr2 = new Mult(new Num(3), new Var("y"));
    CHECK(multExpr2->has_variable() == true);
    
    Expr* multExpr3 = new Mult(new Num(3), new Var("y"));
    CHECK(multExpr3->has_variable() == true);
    
    Expr* multExpr4 = new Mult(new Num(3), new Num(3));
    CHECK(multExpr4->has_variable() == false);
}

TEST_CASE("VARIABLE NO EXCEPTION") {
    CHECK_THROWS_WITH( (new Var("x"))->interp(), "No value for variable!" );
    CHECK_THROWS_WITH( (new Var("y"))->interp(), "No value for variable!" );
}

TEST_CASE("EXPRESSION CONTAINS VARIABLE") {
    CHECK( (new Add(new Var("x"), new Num(1)))->has_variable() == true );
    CHECK( (new Mult(new Num(2), new Num(1)))->has_variable() == false );
    CHECK( (new Add(new Num(2), new Num(1)))->has_variable() == false );
}

TEST_CASE("SUBST ADD") {
    Expr* expr = new Add(new Var("x"), new Num(7));
    Expr* substitutedExpr = expr->subst("x", new Num(10));
    // Check if the substituted expression equals the expected result (10 + 7)
    CHECK(substitutedExpr->equals(new Add(new Num(10), new Num(7))) == 1);
    //Check if the substituted expression equals the expected result (y + 7)
    CHECK( (new Add(new Var("x"), new Num(7)))
          ->subst("x", new Var("y"))
          ->equals(new Add(new Var("y"), new Num(7))) );
    //Check if the substituted expression equals the expected result (y+ 7)
    CHECK( (new Var("x"))
           ->subst("x", new Add(new Var("y"),new Num(7)))
           ->equals(new Add(new Var("y"),new Num(7))) );
}

TEST_CASE("SUBST MULT") {
    Expr* expr = new Mult(new Var("x"), new Num(7));
    Expr* substitutedExpr = expr->subst("x", new Num(10));
    // Check if the substituted expression equals the expected result (10 + 7)
    CHECK(substitutedExpr->equals(new Mult(new Num(10), new Num(7))) == 1);
    //Check if the substituted expression equals the expected result (y + 7)
    CHECK( (new Mult(new Var("x"), new Num(7)))
          ->subst("x", new Var("y"))
          ->equals(new Mult(new Var("y"), new Num(7))) );
    //Check if the substituted expression equals the expected result (y+ 7)
    CHECK( (new Var("x"))
           ->subst("x", new Mult(new Var("y"),new Num(7)))
           ->equals(new Mult(new Var("y"),new Num(7))) );
}


