gpgcrack
========

Cracks OpenPGP private keys

1. Compile gpgcrack ```make```

2. ```cat ~/magnum-jumbo/run/password.lst  | ./gpgcrack <GPG Secret Key>```

3. ```john -i -stdout | ./gpgcrack <GPG Secret Key>```

Note: For brute-forcing PGP private key files use JtR-jumbo instead of this program!