CRYPTODEV on linux
==================

Interesting links :

- Articles
  - http://ocf-linux.sourceforge.net/benchmarks.html
- Softwares with cryptodev support
  - https://github.com/tchar/cryptodev-python
  - https://github.com/openssl/openssl
  - https://github.com/MISL-EBU-System-SW/mainline-public/issues/42

---

Bench OpenSSL
-------------

    apt-get install gcc
    modprobe cryptoloop || true
    git clone https://github.com/openssl/openssl.git
    cd openssl && ./config --with-cryptodev && make
