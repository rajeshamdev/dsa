
# Reverse a string. Note that string are immutable in python
# so we cannot swap sring ends which could be little efficient.
def reverseString(name):
    strlen = len(name)
    rev =""
    for i in range(strlen):
       rev += name[strlen-i-1]
    return rev

rev = reverseString("Veritas Interview")
print rev
rev = reverseString(rev)
print rev
