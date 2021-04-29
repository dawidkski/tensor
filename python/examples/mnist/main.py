import time
from typing import List

import numpy as np
from tqdm import tqdm

import tensor as ts
from tensor.autograd import Variable

from dataset import MNISTDataset

MODEL_SAVE_NAME = "mnist_model.ts"


class Net(ts.libtensor.LayerBase):
    def __init__(self):
        super().__init__()
        self.conv1 = ts.nn.Conv2D(1, 32, 3, 1, 0, 1, activation=ts.nn.Activation.RELU, use_bias=False)
        self.conv2 = ts.nn.Conv2D(32, 64, 3, 1, 0, 1, activation=ts.nn.Activation.RELU, use_bias=False)
        self.fc1 = ts.nn.Linear(9216, 128, activation=ts.nn.Activation.RELU)
        self.fc2 = ts.nn.Linear(128, 10)
        self.max_pool = ts.nn.MaxPool2D(2, 2, 0)

        self._register()

    def forward(self, x: Variable) -> Variable:
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.max_pool(x)
        x = ts.autograd.reshape(x, [-1, 9216])
        x = self.fc1(x)
        x = self.fc2(x)
        return x

    def weights(self) -> List[List[ts.libtensor.GradHolderF]]:
        return [self.conv1.weights(), self.conv2.weights(), self.fc1.weights(), self.fc2.weights()]

    def _register(self):
        self.register_parameters(self.conv1.parameters())
        self.register_parameters(self.conv2.parameters())
        self.register_parameters(self.fc1.parameters())
        self.register_parameters(self.fc2.parameters())


def train() -> None:
    normalize = lambda images: (images - 0.1307) / 0.3081
    dataset_train = MNISTDataset("./data", train=True, batch_size=32, transform=normalize)

    model = Net()
    loss_fn = ts.nn.CrossEntropyLoss()
    optimizer = ts.libtensor.SGD(0.01)
    saver = ts.libtensor.Saver(model)

    for w in model.weights():
        optimizer.register_params(w)

    time_start = time.time()
    for batch_idx, (data, target) in enumerate(dataset_train):
        x = Variable(data)
        y = Variable(target)

        output = model.forward(x)
        loss = loss_fn(output, y)
        loss.backward()
        optimizer.step()

        if batch_idx != 0 and batch_idx % 10 == 0:
            print("Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}".format(
                1, batch_idx * dataset_train.batch_size, dataset_train.example_num,
                   100.0 * batch_idx / len(dataset_train), loss.value[0]))
    time_end = time.time()
    print(f"Training time: {time_end - time_start}")

    saver.save(MODEL_SAVE_NAME)


def eval() -> None:
    normalize = lambda images: (images - 0.1307) / 0.3081
    dataset = MNISTDataset("./data", train=False, batch_size=32, transform=normalize)
    model = Net()
    saver = ts.libtensor.Saver(model)
    saver.load(MODEL_SAVE_NAME)

    correct = 0
    for data, target in tqdm(dataset):
        x = Variable(data)
        y = Variable(target)
        output = model.forward(x)
        pred = ts.argmax(output.value)
        correct += np.sum(pred.numpy == y.value.numpy)

    print('\nTest set: Accuracy: {}/{} ({:.0f}%)\n'.format(
        correct, dataset.example_num, 100. * correct / dataset.example_num))


if __name__ == '__main__':
    train()
    eval()
