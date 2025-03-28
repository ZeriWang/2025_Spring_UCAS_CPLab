
    #include <vector>


// Generated from Hello.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "HelloParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by HelloParser.
 */
class  HelloVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HelloParser.
   */
    virtual std::any visitR(HelloParser::RContext *context) = 0;


};

