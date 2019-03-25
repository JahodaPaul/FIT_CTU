# 0 - establish connection
# 1 - service number 1
# 2 - service number 2
# 3 - service number 3
# 4 - service number 4
# 5 - non-idempotent service - check number of flights
# 6 - idempotent service - give this information service a like and retrieve how many likes this system has

# 11 - int
# 12 - string
# 13 - date-time
# 14 - floating point
# 15 - flight

INT = 11
STR = 12
DATE = 13
FP = 14
FLI = 15

AT_LEAST_ONCE = 100
AT_MOST_ONCE = 101

# 126 - error message
ERROR = 126