* This is a one-time encryption and decryption algorithm based on the "JunTai"(like Shuffle) distribution random number algorithm.
* The so-called "JunTai" distribution random number algorithm refers to: each number (integer or real number) is distributed disorderly on the number axis, its value appears only once without repetition.
* Of course, my algorithm here is not true "JunTai" distribution random number algorithm, because the value of the key table is from 0 to 255, and the key value is the cyclic repetition of these 256 values.
* If the key table is infinite, it is just the true "JunTai" distribution random number algorithm. Because infinity, all the values are not repeated once, and the positions are disorderly.
* As long as they are repeated once, they can not be called "JunTai" distribution random number algorithm.
* In fact, it is an implementation of Shannon encryption algorithm, but it only corrects the defect that the key stream should be the same length as the plaintext.
* The key is to use password and key table to generate key stream of the same length as plaintext.
* That is to say, using password and key table to shorten the length of key stream, and then using "JunTai" distribution random number algorithm to restore the key stream of the same length as plaintext.

* It's just a demo version, the official version includes lower version, intermediate version and advanced version.
* If you want to source code of official version, please contact me.
* I hope who can crack this algorithm one day in my lifetime.
* If you break this algorithm, please let me know. Thank you very so much!

* Compiled on MacOS, Linux and *BSD in X86_64 platform.
