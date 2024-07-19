#!usr/bin/env python 

import tensorflow as tf 
import numpy as np
import matplotlib.pyplot as plt 
import os 
from PIL import Image


# Add noise to the old image
def noise_image(image):
    # Modify pixel values with noise
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            std_dev = 0.1 * image[i, j]
            for k in range(1):

                # Add noise to pixel value
                image[i, j] = min(max(image[i, j] + np.random.normal(0.02, std_dev), 0), 1)
                image[i, j] = max(0, 1 / (1 + 110 * np.exp(-36 * image[i, j]))) #36
                image[i, j] = min(max(image[i, j] + np.random.normal(0.02, std_dev), 0), 1)
    return image



def main():
    
    # ========================
    # FULL DATASET IMAGE NOISE 
    # ========================

    # If the noise dataset already exists skip this seciton
    if not os.path.exists('noisy_mnist.npz'):
        print("Creating Noise dataset!")

        # Upload 20.000 elements from MNIST dataset
        (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
        idx_original = np.random.choice(len(x_train), 30000, replace=False)
        x_train_original_subset = x_train[idx_original]
        y_train_original_subset = y_train[idx_original]
    
        x_train_original_subset = x_train_original_subset.astype(np.float32) / 255.0

        # Add noise
        noisy_dataset = np.array([noise_image(image) for image in x_train_original_subset])

        # Save the noisy dataset
        np.savez('noisy_mnist.npz', x_train=noisy_dataset, y_train=y_train_original_subset)
    else:
        print("Noise dataset already exists!")


    # If the combined dataset already exists skip this seciton
    if not os.path.exists('combined_mnist_noisy_dataset.npz'):
        print("Creating Combined - Noise dataset!")

        # Load the noisy dataset
        data = np.load('noisy_mnist.npz')
        x_train_noisy = data['x_train']
        y_train_noisy = data['y_train']

        print("Noise x_train shape:", x_train_noisy.shape)
        print("Noise y_train shape:", y_train_noisy.shape)

        # Upload 10.000 elements from MNIST dataset
        (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
        idx_original = np.random.choice(len(x_train), 30000, replace=False)
        x_train_original_subset = x_train[idx_original]
        y_train_original_subset = y_train[idx_original]

        x_train_original_subset = x_train_original_subset.astype(np.float32) / 255.0

        x_combined = np.concatenate((x_train_original_subset, x_train_noisy), axis=0)
        y_combined = np.concatenate((y_train_original_subset, y_train_noisy), axis=0)

        # Shuffle the combined dataset
        indices = np.arange(len(x_combined))
        np.random.shuffle(indices)
        x_combined = x_combined[indices]
        y_combined = y_combined[indices]

        np.savez('combined_mnist_noisy_dataset.npz', x_train=x_combined, y_train=y_combined)


        print("Combined x_train shape:", x_combined.shape)
        print("Combined y_train shape:", y_combined.shape)
    
    else:
        print("Combined dataset alreday exists!")

    print("Dataset Available!")



    dataset = np.load('combined_mnist_noisy_dataset.npz')
    x_train = dataset['x_train']
    y_train = dataset['y_train']

        # Display a sample of noisy images
    #plt.figure(figsize=(10, 5))
    for i in range(20):
        #plt.subplot(2, 5, i + 1)
        plt.imshow(x_train[i], cmap='gray')
        plt.title(f"{y_train[i]}")
        plt.axis('off')
        plt.show()


if __name__ == '__main__':
    main()
