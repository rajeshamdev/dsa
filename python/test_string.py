import pytest
from strings import StringsInterviewPrep

def test_invalid_input():
    with pytest.raises(ValueError, match="input must be string"):
        StringsInterviewPrep.reverse(123)  # Not a string


class TestStringsInterviewPrep:
    @pytest.mark.parametrize("input_str, expected", [
        ("hello", "olleh"),
        ("", ""),
        ("a", "a"),
        ("12345", "54321"),
        ("racecar", "racecar"),
        ("hello world", "dlrow olleh"),
    ])
    def test_reverse_string(self, input_str, expected):
        assert StringsInterviewPrep.reverse(input_str) == expected

    @pytest.mark.parametrize("input_str, expected", [
        ("A man, a plan, a canal, Panama", True),
        ("No 'x' in Nixon", True),
        ("Hello, World!", False),
        ("", True),
        (" ", True),
        ("Was it a car or a cat I saw?", True),
        ("Not a palindrome", False),
        ("12321", True),
        ("12345", False),
    ])
    def test_isPalindrome(self, input_str, expected):
        assert StringsInterviewPrep.isPalindrome1(input_str) == expected
        assert StringsInterviewPrep.isPalindrome2(input_str) == expected
        assert StringsInterviewPrep.isPalindrome3(input_str) == expected

    @pytest.mark.parametrize("input_str, v, c",  [
        ("hello", 2, 3),
        ("aeioU", 5, 0),
        ("rjshmkj", 0, 7)
    ])
    def test_countVowels(self, input_str, v, c):
        vc, cc = StringsInterviewPrep.countVowelsConsonents(input_str)
        assert v == vc
        assert c == cc
