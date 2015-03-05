#include "Tokenizer.h"

#include <Rcpp.h>
using namespace Rcpp;

#include "TokenizerDelimited.h"

TokenizerPtr tokenizerCreate(List spec) {
  CharacterVector klass = as<CharacterVector>(spec.attr("class"));
  std::string subclass(klass[klass.size() - 1]);

  if (subclass == "tokenizer_delimited") {
    char delim = as<char>(spec["delim"]);
    std::string na = as<std::string>(spec["na"]);

    return TokenizerPtr(new TokenizerDelimited(delim, na));
  }

  Rcpp::stop("Unknown tokenizer type");
  return TokenizerPtr();
}