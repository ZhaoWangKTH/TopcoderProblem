// Topcoder problem: undoHistory.cpp

/*
  The main difficulty of this problem lies in understanding the problem description by going through all the shown test cases. 
*/

/****************
  Problem Description
  Problem Statement
Bob is using a peculiar text editor to write a sequence of lines of text. The editor consists of three parts: a results window, a text buffer and an undo history. More details about the three parts follow.
The results window contains a sequence of strings: the lines of text you already wrote. Initially, the results window is empty.
The text buffer contains a string: the line you are writing at the moment. Initially, the string in the text buffer is empty.
The undo history contains a sequence of strings: all the past states of the text buffer. Initially, the undo history contains a single element: an empty string.
You are given a lines. Bob would like to print the contents of lines into the results window. (At the end, the sequence of strings stored in the results window must be precisely equal to lines. Order of elements matters.) Additionally, Bob would like to do so as quickly as possible. He is able to take the following actions:
Bob may type a lowercase letter. The letter is appended to the text buffer. The new text buffer is then added as a new element of the undo history. (For example, if the text buffer currently contains "do", then pressing 'g' changes the text buffer to "dog" and then stores "dog" into the undo history.)
Bob may press Enter. When he does so, the current content of the text buffer is printed to the results window as a new line, after the lines that were printed earlier. The text buffer remains unmodified. (For example, if the text buffer contains "dog" and Bob presses Enter, "dog" will be appended to the results window, and the results buffer still contains "dog".)
Bob may use two mouse clicks to restore any entry from the undo history to the text buffer. This operation does not modify the undo history.
Return the minimum total number of button presses (keyboard and mouse) that Bob needs to print all the given lines into the results window.

Examples
0)
{"tomorrow", "topcoder"}
Returns: 18
Type 't'. The text buffer now contains "t", and the undo history now contains "" and "t".
Type 'o'. The text buffer now contains "to", and the undo history now contains "", "t", and "to".
Using six more keypresses, type the letters in "morrow". The text buffer now contains "tomorrow" and the undo history contains all prefixes of "tomorrow". The results window is still empty.
Press Enter. The results window now contains one string: "tomorrow".
Click the mouse twice to restore "to" from undo history.
Using another six keypresses, type the letters in "pcoder".
Press Enter. The results window now contains "tomorrow" and "topcoder", in this order, and we are done.
The total number of button presses was 8 (typing "tomorrow") + 1 (Enter) + 2 (mouse) + 6 (typing "pcoder") + 1 (Enter) = 18.
1)
{"a","b"}
Returns: 6
After typing "a" and pressing enter, we need to restore the empty string (which is always present at the top of the undo buffer) before typing "b".
2)
{"a", "ab", "abac", "abacus" }
Returns: 10
There are times when it is not necessary to use the undo history at all.
3)
{"pyramid", "sphinx", "sphere", "python", "serpent"}
Returns: 39
4)
{"ba","a","a","b","ba"}
Returns: 13
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.

******************/

// HERE ARE THE CODES //

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class UndoHistory{
	public: int minPresses(vector<string> &lines);
    private: 
    	bool isPrefix(string prev, string cur){ // check if prev is a prefix of cur
            if(prev.size() > cur.size())
                return false;
            for(int i=0; i<prev.size(); i++)
            {
                if(prev[i]!=cur[i])
                    return false;
            }
            return true;
    	};
    	int prefNum(string A, string B){
        	if(A.size() > B.size())
                return prefNum(B, A);
            int len = 0;
            while(A[len] == B[len] && len < A.size())
                len++;
            
            return len;
        };
};

int UndoHistory::minPresses(vector<string> &lines){
    int res = 0;
    for(int i=0; i<lines.size(); i++)
    {
        int pref_num= 0;
        for(int j=0; j<i; j++)
            pref_num = max(pref_num, prefNum(lines[j], lines[i]));
        
        // now try to compare
        if(i>0 && isPrefix(lines[i-1], lines[i]))
            res += min(lines[i].size()-lines[i-1].size()+1, 2+(lines[i].size()-pref_num)+1);
        else if(i>0)
            res += 2+(lines[i].size()-pref_num)+1;
        else // i=0    
    		res += lines[i].size()+1;
    }
    
    return res;
}
