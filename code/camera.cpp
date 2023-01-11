#include <iostream>
#include <webots/Robot.hpp>
#include <opencv2/opencv.hpp>

using namespace webots;
using namespace cv;
using namespace std;

// INITIALIZATIONS
Robot *robot = new Robot();
int timeStep = (int)robot->getBasicTimeStep();      // Set the time step for the simulation

// Camera Initialization
Camera *cam = robot->getCamera("camera1");
cam->enable(timeStep);

// Variables declaration
const unsigned char image;
int translations;


// UTILITIES FOR THE CAMERA
// normalizes the degs of the rotation
int normalizeDegs(ang):
    int ang = ang % 360
    if ang < 0 {
        int ang += 360;
    }
    if ang == 360 {
        int ang = 0;
    }

    return ang;

//get_image obtais the video footage from the camera
int get_image(image) {
        const unsigned char image = *getImage();
        return image;
}

class Camera (get_image()) {
    public:
        const unsigned char image;
    
    //sharpen_image makes the image clearer and lowers noise
    int sharpen_image(image) {
        int kernel[9] = {[[-1,-1,-1], [-1,5,-1], [-1,-1,-1]]};
        unsigned char image = filter2D(image, -1, kernel);
        return image;
    }

    //upscale_image makes the image bigger by resizing it
    int upscale_image(image) {
        int resized_image = resize(image, (0,0), fx=scale, fy=scale, interpolation=INTER_CUBIC);
        Mat image = resized_image;
        return image;
    }

    //flatten_image changes the image perspective, and instead of pointing directly at a wall, points at the corner of the wall and the floor,
    //making it easier to identify the floor type and the victims.
    int flatten_image(image) {
        int tiles_up = 2;
        int tiles_down = 0;
        int tiles_side = 1;

        int tile_resolution = 100;

        int minumum_x = tile_resolution * tiles_side;
        int maximum_x = tile_resolution * (tiles_side + 1);
        int minumum_y = tile_resolution * (tiles_up);
        int maximum_y = tile_resolution * (tiles_up + 1) -40;

        Mat img_points = array(([5, 6],  [35, 6], [31, 3], [8, 3], ), dtype=np.float32);

        Mat final_points = array(([minimum_x, minimum_y],  [maximum_x, minimum_y], [maximum_x, maximum_y], [minimum_x, maximum_y],), dtype=np.float32);

        Mat ipm_matrix = getPerspectiveTransform(img_points, final_points, solveMethod=DECOMP_SVD);

        int final_x = tile_resolution * ((tiles_side *2) + 1);
        int final_y = tile_resolution * (tiles_up + 1 + tiles_down);

        int final_y_modified = round(final_y * 1);

        Mat ipm = warpPerspective(image, ipm_matrix, (final_x, final_y_modified), flags=INTER_NEAREST);
        Mat ipm = resize(ipm, (final_x, final_y), interpolation=INTER_CUBIC);

        return ipm;
    }

    //after changing the perspective of the image, overlay_image_alpha cuts it.
    int overlay_image_alpha() {
        int y1, y2 = max(0, y), min(img.shape[0], y + img_overlay.shape[0]);
        int x1, x2 = max(0, x), min(img.shape[1], x + img_overlay.shape[1])

        Mat y1o, y2o = max(0, -y), min(img_overlay.shape[0], img.shape[0] - y)
        Mat x1o, x2o = max(0, -x), min(img_overlay.shape[1], img.shape[1] - x)


        if y1 >= y2 or x1 >= x2 or y1o >= y2o or x1o >= x2o {
            return
        }

        Mat img_crop = img[y1:y2, x1:x2]
        Mat img_overlay_crop = img_overlay[y1o:y2o, x1o:x2o]
        Mat alpha = alpha_mask[y1o:y2o, x1o:x2o, np.newaxis]
        Mat alpha_inv = 1.0 - alpha

        Mat img_crop[:] = img_overlay_crop * alpha + img_crop * alpha_inv

    }

    //join_camera_images puts the different images all together and overlays them.
    int join_camera_images(images, translations) {
        int max_x = 0;
        int max_y = 0;

        for(translation : translations){  
            int max_x = max(max_x, translation[1]);
            int max_y = max(max_y, translation[0]);
        }  
        Mat background = zeros((max_x + images[0].shape[1], max_y + images[0].shape[0], 3), dtype=uint8);
    }

    //rotate_image rotates the image
    int rotate_image(image, robot_rotation) {
        int rot = normalizeDegs(robot_rotation);
        return rotate(image, rot); 
    }

    //get_floor_image creates a sort of separate image that only frames the floor, ignoring the wall.
    int get_floor_image(images, robot_rotation) {
        list<Mat>{};

        for(img : images){
            Mat img = rot90(img, 3, (0,1));
            Mat img = flatten_image(img);
            Mat img = flip(img, 0);
            flattened_images.append(img)
        }

        int x_red = 5;
        int y_red = 2;

        int translations = [[200 - y_red, 400 - x_red], [400 - x_red, 200 + y_red], [200 + y_red, 0 + x_red]];
        Mat camera_final_image = join_camera_images(flattened_images, translations);

        return rotate_image(camera_final_image, robot_rotation - 90);
    }

}
// FUNCTIONS FOR THE CAMERA

/*
int main()
{
    const unsigned char image;

    while (robot->step(timeStep) != -1)
    {
		get_image(image)
    }
}
*/