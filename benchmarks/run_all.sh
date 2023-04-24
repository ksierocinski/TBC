#!/bin/bash
echo "Starting benchmark latency QT"
./01_latency/01_latency_QT >> 01_latency_QT.out

echo "Starting benchmark latency TBC"
./01_latency/01_latency_TBC >> 01_latency_TBC.out

echo "Starting benchmark const to const QT"
./02_const_to_const/02_const_to_const_QT >> 02_const_to_const_QT.out

echo "Starting benchmark const to const TBC"
./02_const_to_const/02_const_to_const_TBC >> 02_const_to_const_TBC.out

echo "Starting benchmark const to value QT"
./03_const_to_value/03_const_to_value_QT >> 03_const_to_value_QT.out

echo "Starting benchmark const to value TBC"
./03_const_to_value/03_const_to_value_TBC >> 03_const_to_value_TBC.out

echo "Starting benchmark rvalue to value QT"
./04_rvalue_to_value/04_rvalue_to_value_QT >> 04_rvalue_to_value_QT.out

echo "Starting benchmark rvalue to value TBC"
./04_rvalue_to_value/04_rvalue_to_value_TBC >> 04_rvalue_to_value_TBC.out

echo "Starting benchmark 1 to 4 const to const QT"
./05_const_to_const_1_to_4/05_const_to_const_1_to_4_QT >> 05_const_to_const_1_to_4_QT.out

echo "Starting benchmark 1 to 4 const to const TBC"
./05_const_to_const_1_to_4/05_const_to_const_1_to_4_TBC >> 05_const_to_const_1_to_4_TBC.out

echo "Starting benchmark 1 to 4 const to value QT"
./06_const_to_value_1_to_4/06_const_to_value_1_to_4_QT >> 06_const_to_value_1_to_4_QT.out

echo "Starting benchmark 1 to 4 const to value TBC"
./06_const_to_value_1_to_4/06_const_to_value_1_to_4_TBC >> 06_const_to_value_1_to_4_TBC.out

echo "Starting benchmark 1 to 4 rvalue to value QT"
./07_rvalue_to_value_1_to_4/07_rvalue_to_value_1_to_4_QT >> 07_rvalue_to_value_1_to_4_QT.out

echo "Starting benchmark rvalue to value TBC"
./07_rvalue_to_value_1_to_4/07_rvalue_to_value_1_to_4_TBC >> 07_rvalue_to_value_1_to_4_TBC.out
