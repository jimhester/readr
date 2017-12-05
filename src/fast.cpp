#include "Rcpp.h"
#include "csv.h"

using namespace Rcpp;
// [[Rcpp::export]]
List read_trip_fare(std::string filename) {
  size_t n = 14776616;
  std::vector<std::string> names = {"medallion",
                                    "hack_license",
                                    "vendor_id",
                                    "pickup_datetime",
                                    "payment_type",
                                    "fare_amount",
                                    "surcharge",
                                    "mta_tax",
                                    "tip_amount",
                                    "tolls_amount",
                                    "total_amount"};
  List out(11);
  out[0] = Rf_allocVector(STRSXP, n);
  out[1] = Rf_allocVector(STRSXP, n);
  out[2] = Rf_allocVector(STRSXP, n);
  out[3] = Rf_allocVector(STRSXP, n);
  out[4] = Rf_allocVector(STRSXP, n);
  out[5] = Rf_allocVector(REALSXP, n);
  out[6] = Rf_allocVector(REALSXP, n);
  out[7] = Rf_allocVector(REALSXP, n);
  out[8] = Rf_allocVector(REALSXP, n);
  out[9] = Rf_allocVector(REALSXP, n);
  out[10] = Rf_allocVector(REALSXP, n);

  io::CSVReader<11> in(filename);
  in.read_header(
      io::ignore_extra_column,
      "medallion",
      "hack_license",
      "vendor_id",
      "pickup_datetime",
      "payment_type",
      "fare_amount",
      "surcharge",
      "mta_tax",
      "tip_amount",
      "tolls_amount",
      "total_amount");
  char *medallion, *hack_license, *vendor_id, *pickup_datetime, *payment_type;
  double fare_amount, surcharge, mta_tax, tip_amount, tolls_amount,
      total_amount;
  size_t i = 0;
  while (in.read_row(
      medallion,
      hack_license,
      vendor_id,
      pickup_datetime,
      payment_type,
      fare_amount,
      surcharge,
      mta_tax,
      tip_amount,
      tolls_amount,
      total_amount)) {
    SET_STRING_ELT(out[0], i, Rf_mkCharCE(medallion, CE_UTF8));
    SET_STRING_ELT(out[1], i, Rf_mkCharCE(hack_license, CE_UTF8));
    SET_STRING_ELT(out[2], i, Rf_mkCharCE(vendor_id, CE_UTF8));
    SET_STRING_ELT(out[3], i, Rf_mkCharCE(pickup_datetime, CE_UTF8));
    SET_STRING_ELT(out[4], i, Rf_mkCharCE(payment_type, CE_UTF8));
    REAL(out[5])[i] = fare_amount;
    REAL(out[6])[i] = surcharge;
    REAL(out[7])[i] = mta_tax;
    REAL(out[8])[i] = tip_amount;
    REAL(out[9])[i] = tolls_amount;
    REAL(out[10])[i] = total_amount;
    i++;
  }
  out.attr("names") = names;
  out.attr("class") = "data.frame";
  out.attr("row.names") = Rcpp::IntegerVector::create(NA_INTEGER, -n);
  return out;
}
