# FDF
A little program that provide a wireframe model of a map.

![fdf42](https://user-images.githubusercontent.com/114223678/194014995-be486422-4603-474e-9aa2-aba664e6d2c5.png)
42.fdf

![fdft2](https://user-images.githubusercontent.com/114223678/194015016-93e15c1f-925d-46fe-a001-7b7ef8a7000f.png)
t2.fdf

To use :
```
$ make
$ ./fdf myfile.fdf
```
myFile.fdf contains a series of numbers separated by spaces, which correspond to the elevation of each point on the map.
Examples are available in the test_maps folder.
The mlx_linux is provide by school 42, it is a small graphics library in C language.
