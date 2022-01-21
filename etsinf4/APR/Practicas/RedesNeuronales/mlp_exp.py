#!/usr/bin/env python
# coding: utf-8

# # Aplicación de redes MLP a la tarea MNIST 

# Importamos las librerías necesarias para la realización de un
# experimento con una red MLP en MNIST

import torch
import torchvision

# ## Carga de datos de MIST

# La tarea MNIST está disponible desde la libreria
# `torchvision`. Mediante el parámetro `train=True` seleccionamos la
# partición de entrenamiento o evaluación. Finalmente, mediante el
# parámetro `transform=torchvision.transforms.ToTensor()` indicamos
# qué transformación se aplica a MNIST, en este caso convertimos las
# imágenes en tensores.

# MNIST Dataset (Images and Labels)
training_dataset = torchvision.datasets.MNIST(
    root='./data',
    train=True,
    transform=torchvision.transforms.ToTensor(),
    download=True
)
test_dataset = torchvision.datasets.MNIST(
    root='./data',
    train=False,
    transform=torchvision.transforms.ToTensor(),
    download=True
)


# ## Diseño experimental y preparación de datos

# Realizamos una partición del conjunto de entrenamiento oficial
# dedicando un 90% (54000 muestras) para entrenamiento y un 10% (6000
# muestras) para validación.

train_dataset, val_dataset = torch.utils.data.random_split(training_dataset, lengths=[54000, 6000])


# A la hora de entrenar el modelo pasaremos los datos por dicho modelo
# varias veces. Cada vez que pasemos un lote de datos (*batch*) por el
# modelo le llamaremos iteración, o *forward pass*. Cada vez que
# pasemos todos los datos por el modelo le llamaremos *epoch*.
# 
# Entre cada epoch los datos son barajados y divididos en lotes
# (batches) de nuevo. Esta gestión de los datos está implementada en
# la clase *DataLoader* de PyTorch.

batch_size = 100

# Preparamos los conjuntos de entrenamiento y validación en lotes y
# barajamos el conjunto de entrenamiento
train_loader = torch.utils.data.DataLoader(dataset=train_dataset, batch_size=batch_size, shuffle=True)
val_loader = torch.utils.data.DataLoader(dataset=val_dataset, batch_size=batch_size, shuffle=False)


# ## Definición de una red MLP
#
# Una red MLP está compuesta por una secuencia de capas de neuronas
# conectadas entre si. La capa de entrada tiene una dimensionalidad
# que depende de los datos utilizados. En el caso de MNIST son
# imágenes de 28x28 píxeles, es decir, 784 dimensiones. La capa de
# salida tiene una dimensionalidad que depende del número de clases a
# predecir. En MNIST, tenemos los dígitos del 0 al 9, es decir, 10
# clases. Entre las capas de entrada y de salida se definen $L$ capas
# ocultas con un número de neuronas $M_l$. A la salida de cada neurona
# se aplica una función de activación para poder aproximar funciones
# no lineales.
# 
# Definimos una red MLP con las siguientes características:
# 
# - Entrada: 784
# - Primera capa oculta ($M_1$): 500
# - Segunda capa oculta ($M_2$): 300
# - Capa de salida: 10
# 
# Usaremos como función de activación ReLU tras cada oculta, pero se
# pueden utilizar otras definidas en el paquete `torch.nn.functional`.

from torch import nn, optim
from torch.nn.modules import Module

class MLP(nn.Module):
    # layers_data is a list of pairs: number of neurons and activation function
    def __init__(self, input_size, layers_data: list, num_classes, learning_rate=1e-3, optimizer=optim.Adam):
        super().__init__()

        self.layers = nn.ModuleList()
        self.input_size = input_size
        # Layer and activation function are appended in a list
        for output_size, activation_function in layers_data:
            self.layers.append(nn.Linear(input_size, output_size))
            input_size = output_size 
            self.layers.append(activation_function)
        # Finally, the output layer is appended
        self.layers.append(nn.Linear(input_size, num_classes))
        if torch.cuda.is_available(): print("Using GPU")
        else: print("Using CPU")
        self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        self.to(self.device)
        self.learning_rate = learning_rate
        self.optimizer = optimizer(params=self.parameters(), lr=learning_rate)
        self.criterion = nn.CrossEntropyLoss()

    def forward(self, input_data):
        for layer in self.layers:
            output_data = layer(input_data)
            input_data=output_data
        return output_data


input_size=28 * 28
M1, M2 = 500, 300
num_classes=10
mlp = MLP(input_size, [(M1, nn.ReLU()), (M2, nn.ReLU())], num_classes)


# ##Entrenamiento de la red MLP
# 
# Se recorre el conjunto de entrenamiento en lotes (batches) y por
# cada batch se efectúan los siguientes pasos:
# 
# 1) Se transfiere el batch a la CPU o GPU.
# 2) Se calcula el paso forward para obtener la predicción.
# 3) Se calcula la función de pérdida y el gradiente utilizando BackProp (backward).
# 4) Se actualizan los valores de los parámetros con el gradiente.
# 5) Se resetea el gradiente.



# Loop for a number of epochs
for epoch in range(20):
    total_loss = 0.0
    
    # Loop over the training set in batch mode
    for (inputs, labels) in train_loader:
        
        # Transfering data to GPU or CPU
        inputs = inputs.to(mlp.device)
        labels = labels.to(mlp.device)

        # Converting from 28x28 data samples to 768 data samples
        inputs = inputs.view(-1, 28*28)
         
        # Forward pass
        outputs = mlp(inputs)
        # Computing loss function 
        loss = mlp.criterion(outputs, labels)
        # Computing gradient
        loss.backward()
        # Updating parameter values with gradient
        mlp.optimizer.step()
        # Reset gradient
        mlp.optimizer.zero_grad()

        # Accumulated loss function over an epoch
        total_loss += loss.item()
        
    print("Epoch %d, Loss=%.4f" % (epoch+1, total_loss/len(train_loader)))


# ### Evaluación
# Estimación del error empírico en un conjunto de datos.

def error(model, data_loader, device):
    with torch.no_grad():
        errors = 0
        total = 0
        for inputs, labels in data_loader:
            inputs = inputs.to(device)     
            inputs = inputs.view(-1, 28*28)
            
            outputs = model(inputs)
            _, predicted = outputs.max(1)
            
            errors += (predicted.cpu() != labels).sum().item()
            total += labels.size(0)
            
    err = errors / total
    return err


# Estimación del error en el conjunto de entrenamiento.

err=error(mlp, train_loader, mlp.device)
print("Tasa de error en entrenamiento: %.2f%%" % (err*100))


# Estimación del error en el conjunto de validación.

err=error(mlp, val_loader, mlp.device)
print("Tasa de error en validación: %.2f%%" % (err*100))
