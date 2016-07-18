context("read-log")

test_that("example log works", {
  x <- read_log(readr_example("example.log"))
  expect_equal(x$X1, c("172.21.13.45", "127.0.0.1"))

  expect_equal(x$X6, c(200, 200))
})
