# Sprawozdanie z ćwiczenia nr 1

Dodano tmux zgodnie ze slajdami z wykładu do obu obrazów za pomocą:
- `BR2_PACKAGE_TMUX=y`
- `BR2_GENERATE_LOCALE="en_US.UTF-8"`

Dla initramfs wyłączono wykonywanie `board/raspberrypi4-64/post-image.sh` który spodziewa się rootfs za pomocą:
- `BR2_ROOTFS_POST_IMAGE_SCRIPT=""` 

Dla rootfs zwiększono rozmiar do 128M, tak aby kompilacja przebiegła pomyślnie.
