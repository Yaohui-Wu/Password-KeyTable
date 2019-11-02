 * This is a one-time encryption and decryption algorithm based on the random number of "JUNTAI" distribution.
 * In fact, it is an implementation of Shannon encryption algorithm, but it only corrects the defect that the secret key should be the same length as the plaintext.
 * The key is to use cipher and secret key table to generate secret key of the same length as plaintext, that is to say,
 * using cipher and secret key table to shorten the length of secret key,
 * and then using "JUNTAI" distribution random number algorithm to restore the secret key of the same length as plaintext.
 * This is a demo version, as well as the official version, enhanced version and ultimate version. If you need source code, please contact me.
 * I hope who can crack it one day in my lifetime. WOW!
 
 * This method of key separation adopts a kind of technology applied to military affairs in ancient China.
* It's about army token, which is called JIAGUFU, so this technology is called JIAGUFU technology.
* I will not explain the description of JIAGUFU. Interested foreign friends can understand the history of ancient Chinese war.

* The random numbers of "JUNTAI" distribution are described as follows:
* each integer is arranged in different positions of the number axis in disorder, and the value only appears once without repetition.
* Of course, my algorithm here is not really "JUNTAI" distribution, because the value of the secret key table is from 0 to 255, and the key is the cyclic repetition of these 256 values.
* If the secret key table is infinite, it is the real JUNTAI distribution. Because infinity, all the values are not repeated once, and the positions are disorderly.
* As long as they are repeated once, they can not be called JUNTAI distribution random numbers.
