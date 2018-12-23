#!/bin/bash

BACKEND=$(cat src/Backend/*.cpp src/Backend/*.h 2>/dev/null | wc -l)
FRONTEND=$(cat src/Frontend/*.cpp src/Frontend/*.h 2>/dev/null | wc -l)
OSTATNI=$(cat src/*.cpp src/*.h 2>/dev/null | wc -l)
CELKEM=$((BACKEND+FRONTEND+OSTATNI))

echo "Frontend: $FRONTEND"
echo "Backend: $BACKEND"
echo "Zbytek: $OSTATNI"
echo "Celkovy pocet radku: $CELKEM"
