# CameraProcessor Function

1) sharpen_image(): it uses "kernel" to sharpen the image, and stores a number of values in an array. That array are the kernel values (how they sharpen the edge of the pixels). Then, a 2D filter is applayed, allowing the image to be sharpened, using the kernel values. It's almost as if the kernel variable provides all the necessary info and the cv.filter2D() method gets the job done.

2) upscale_image(): Resizes the image, making it bigger and easier to see.

3) flatten_image(): this function mkodifies the camera vision, so that it focuses on the bottom of the image, ignoring the upper part. An array contaning the points of the image is created. Then, the method getPerspectiveTransform() is used to change the image's perspective. After that, the image is "shapened" (noise is lowered and the image's perspective is defined) and resized.

4) overlay_image_alpha(): the originial image is overlayed by the modified image. FIrstly, the image ranges of the image are established, and then the sencond image is placed above those ranges, considering tha changes that have alrady been made to it. After that, the two images "melt" and "become one", being the unneecesary ṕart cropped.

5) join_camera_images(): 

6) rotate_image(): 

7) get_floor_image():
