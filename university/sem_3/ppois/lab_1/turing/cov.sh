#!/bin/bash
# Скрипт для генерации отчёта покрытия кода

lcov --capture --directory build --output-file coverage.info --ignore-errors mismatch
genhtml coverage.info --output-directory coverage_html
