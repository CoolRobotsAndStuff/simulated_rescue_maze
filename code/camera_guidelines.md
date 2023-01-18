# CameraProcessor Function

1) sharpen_image(): it uses "kernel" to sharpen the image, and stores a number of values in an array. That array are the kernel values (how they sharpen the edge of the pixels). Then, a 2D filter is applayed, allowing the image to be sharpened, using the kernel values. It's almost as if the kernel variable provides all the necessary info and the cv.filter2D() method gets the job done.

2) upscale_image(): Resizes the image, making it bigger and easier to see.

3) flatten_image():  