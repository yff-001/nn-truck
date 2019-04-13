import numpy as np
import cv2

import socket
import time
import os


class CollectTrainingData(object):
    
    def __init__(self, host, port, input_size):

        self.server_socket = socket.socket()
        self.server_socket.bind((host, port))
        self.server_socket.listen(0)

        # accept a single connection
        self.connection = self.server_socket.accept()[0].makefile('rb')

        self.send_inst = True

        self.input_size = input_size

        # create labels
        self.k = np.zeros((4, 4), 'float')
        for i in range(4):
            self.k[i, i] = 1

    def collect(self):

        saved_frame = 0
        total_frame = 0

        # collect images for training
        #print("Start collecting images...")
        #print("Press 'q' or 'x' to finish...")
        start = cv2.getTickCount()

        X = np.empty((0, self.input_size))
        y = np.empty((0, 4))

        # stream video frames one by one
        try:
            stream_bytes = b' '
            frame = 1
            while self.send_inst:
                stream_bytes += self.connection.read(1024)
                first = stream_bytes.find(b'\xff\xd8') # this searches the bytes stream for ff and d8
                last = stream_bytes.find(b'\xff\xd9') # JPEG image files begin with FF D8 and end with FF D9

                if first != -1 and last != -1:
                    jpg = stream_bytes[first:last + 2]
                    stream_bytes = stream_bytes[last + 2:]
                    # imdeocde(): Reads an image from a buffer in memory
                    image = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), 1) # 1,0,-1 --> colour, grayscale, unchanged
                    
                    # image.shape() returns a tuple of # of rows, columns, channels
                    height, width = image.shape[:2]

                    cv2.imshow('Camera Module V2', image)

                    # reshape 'image' array, 3 channels in colour images
                    temp_array = image.reshape(1, height * width * 3)
                    
                    frame += 1
                    total_frame += 1

                    if cv2.waitKey(1) & 0xFF == ord('q'):
                        break

            # save data as a numpy file
            file_name = str(int(time.time()))
            directory = "training_data"
            if not os.path.exists(directory):
                os.makedirs(directory)
            try:
                np.savez(directory + '/' + file_name + '.npz', train=X, train_labels=y)
            except IOError as e:
                print(e)

            end = cv2.getTickCount()
            # calculate streaming duration
            print("Streaming duration: , %.2fs" % ((end - start) / cv2.getTickFrequency()))

            print(X.shape)
            print(y.shape)
            print("Total frame: ", total_frame)
            print("Saved frame: ", saved_frame)
            print("Dropped frame: ", total_frame - saved_frame)

        finally:
            self.connection.close()
            self.server_socket.close()


if __name__ == '__main__':
    HOST = "192.168.0.13"
    PORT = 65432

    SIZE = 384 * 288

    ctd = CollectTrainingData(HOST, PORT, SIZE)
    ctd.collect()
