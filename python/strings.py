

class StringsInterviewPrep:
    """ A class implementing coding interview questions on strings"""

    def __init__(self):
        pass

    @staticmethod
    def reverse(s: str) -> str:
        """
        Reverse a string

        Args:
            s (str): string input
        """
        if not isinstance(s, str):
            raise ValueError("input must be string")
        return s[::-1]

    @staticmethod
    def isPalindrome1(s: str) -> bool:
        """
        Check if a string is palindrome

        Args:
            s (str): string input
        """

        s = [c.lower() for c in s if c.isalnum()]
        return s == s[::-1]

    @staticmethod
    def isPalindrome2(s: str) -> bool:
        """
        Check if a string is palindrome

        Args:
            s (str): string input
        """

        s = [c.lower() for c in s if c.isalnum()]
        return all(s[i] == s[~i] for i in range(len(s)//2))

    @staticmethod
    def isPalindrome3(s: str) -> bool:
        """
        Check if a string is palindrome

        Args:
            s (str): string input
        """

        s = [c.lower() for c in s if c.isalnum()]
        l = 0
        r = len(s) - 1
        while l < r:
            if s[l] != s[r]:
                return False
            l += 1
            r -= 1

        return True

    @staticmethod
    def countVowelsConsonents(s: str):

        vowels = "aeiouAEIOU"

        v = sum (1 for c in s if c in vowels)
        c = sum (1 for c in s if c not in vowels)
        return v, c
