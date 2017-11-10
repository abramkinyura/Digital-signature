Программа примитивной электронной подписи. Работает в двух режимах - на подпись и на проверку (sign/check)
В режиме подписи - хэширует файл, шифрует хэш, записывает полученное куда скажут.
В режиме проверки - хэширует файл, считывает из указанного файла подпись, дешифрует её, сравнивает, выдает результат.
Прилагаю саму программу и 2 ключа (открытый и тайный соответственно)
Если скопировать программу с этими 2мя файлами в папку BigInt (проект лектора с длинной арифметикой) то компилируется командой
g++ Sign.cpp  BigInt.cpp lariph/laitoa.cpp lariph/lariph.cpp lariph/lmariph.cpp lariph/ladiv.cpp lariph/lamult.cpp -o ESign
Примеры вызова
firewolf@OMW:~/Desktop/Programming/Source Code/C++ Source Code/Study::RSA/BigInt$ ./ESign sign BigInt.cpp BigInt.sgn
Signing initiated
Successful signing

firewolf@OMW:~/Desktop/Programming/Source Code/C++ Source Code/Study::RSA/BigInt$ ./ESign check BigInt.cpp BigInt.sgn
Checking initiated
Hashes are equal. File is confirmed

firewolf@OMW:~/Desktop/Programming/Source Code/C++ Source Code/Study::RSA/BigInt$ ./ESign check BIStack.cpp BigInt.sgn
Checking initiated
Hashes are not equal

