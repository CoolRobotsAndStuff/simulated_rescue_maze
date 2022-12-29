import cv2 as cv
import numpy as np
import utilities
import imutils

class CameraProcessor:
    def __init__(self, tile_resolution):
        self.tile_resolution = tile_resolution # 100

    def sharpen_image(self, image):
        kernel = np.array([[-1,-1,-1], [-1,5,-1], [-1,-1,-1]])
        return cv.filter2D(image, -1, kernel)

    def upscale_image(image, scale):
        return cv.resize(image, (0,0), fx=scale, fy=scale, interpolation=cv.INTER_CUBIC)

    def flatten_image(self, image):
        tiles_up = 2
        tiles_down = 0
        tiles_side = 1

        minimum_x = self.tile_resolution * tiles_side
        maximum_x = self.tile_resolution * (tiles_side + 1)
        minimum_y = self.tile_resolution * (tiles_up)
        maximum_y = self.tile_resolution * (tiles_up  + 1)  - 40

        #robot1_points = np.array(([4, 17], [35, 17],  [31, 12],  [8, 12],), dtype=np.float32)
        img_points = np.array(([5, 6],  [35, 6], [31, 3], [8, 3], ), dtype=np.float32)
        final_points = np.array(([minimum_x, minimum_y],  [maximum_x, minimum_y], [maximum_x, maximum_y], [minimum_x, maximum_y],), dtype=np.float32)

        ipm_matrix = cv.getPerspectiveTransform(img_points, final_points, solveMethod=cv.DECOMP_SVD)
        
        final_x = self.tile_resolution * ((tiles_side * 2) + 1)
        final_y = self.tile_resolution * (tiles_up + 1 + tiles_down)
        
        final_y_modiff = round(final_y * 1)#0.95)

        ipm = cv.warpPerspective(image, ipm_matrix, (final_x, final_y_modiff), flags=cv.INTER_NEAREST)
        ipm = cv.resize(ipm, (final_x, final_y), interpolation=cv.INTER_CUBIC)

        return ipm

    def overlay_image_alpha(self, img, img_overlay, x, y, alpha_mask):
        """Overlay `img_overlay` onto `img` at (x, y) and blend using `alpha_mask`.
        `alpha_mask` must have same HxW as `img_overlay` and values in range [0, 1].
        """
        # Image ranges
        y1, y2 = max(0, y), min(img.shape[0], y + img_overlay.shape[0])
        x1, x2 = max(0, x), min(img.shape[1], x + img_overlay.shape[1])

        # Overlay ranges
        y1o, y2o = max(0, -y), min(img_overlay.shape[0], img.shape[0] - y)
        x1o, x2o = max(0, -x), min(img_overlay.shape[1], img.shape[1] - x)

        # Exit if nothing to do
        if y1 >= y2 or x1 >= x2 or y1o >= y2o or x1o >= x2o:
            return

        # Blend overlay within the determined ranges
        img_crop = img[y1:y2, x1:x2]
        img_overlay_crop = img_overlay[y1o:y2o, x1o:x2o]
        alpha = alpha_mask[y1o:y2o, x1o:x2o, np.newaxis]
        alpha_inv = 1.0 - alpha

        img_crop[:] = img_overlay_crop * alpha + img_crop * alpha_inv

    def join_camera_images(self, images, translations):
        max_x = 0
        max_y = 0

        for translation in translations:
            max_x = max(max_x, translation[1])
            max_y = max(max_y, translation[0])

        backround = np.zeros((max_x + images[0].shape[1], max_y + images[0].shape[0], 3), dtype=np.uint8)
        
        rot_imgs = []
        for index, img in enumerate(images):
            rot_imgs.append(np.rot90(img, index + 2, (0,1)))

        for rot_img, translation in zip(rot_imgs, translations):
            self.overlay_image_alpha(backround, rot_img[:,:,:3], translation[0], translation[1], rot_img[:,:,3] / 255)
        
        return backround.copy()

    def rotate_image(self, image, robot_rotation):
        rot = utilities.normalizeDegs(robot_rotation)
        return imutils.rotate(image, rot)

    def get_floor_image(self, images, robot_rotation):
        flattened_images = []
        for img in images:
            img = np.rot90(img, 3, (0,1))
            img = self.flatten_image(img)
            img = np.flip(img, 0)
            flattened_images.append(img)

        x_red = 5
        y_red = 2

        translations = [[200 - y_red, 400 - x_red], [400 - x_red, 200 + y_red], [200 + y_red, 0 + x_red]]
        camera_final_image = self.join_camera_images(flattened_images, translations)

        return self.rotate_image(camera_final_image, robot_rotation - 90)

if __name__ == "__main__":
    pass