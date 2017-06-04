using MAT

# function for calculating squared distance
function sqdistance(p, q, pSOS, qSOS)
  return broadcast(+, pSOS, qSOS') - 2*p*q'
end

# open file
file = matopen("mnistData.mat")
mnist = read(file, "mnist")

# load data
train_images = mnist["train_images"]
train_labels = mnist["train_labels"]
test_images = mnist["test_images"]
test_labels = mnist["test_labels"]

# set training & testing
trainndx = 1:10000
testndx =  1:10000

ntrain = length(trainndx)
ntest = length(testndx)
Xtrain = float(reshape(train_images[:,:,trainndx], 28*28, ntrain)')
Xtest  = float(reshape(test_images[:,:,testndx], 28*28, ntest)')

ytrain = train_labels[trainndx]
ytest  = test_labels[testndx]

# Precompute sum of squares term
XtrainSOS = sum(Xtrain.^2, 2)
XtestSOS  = sum(Xtest.^2, 2)

# fully solution takes too much memory so we will classify in batches
# nbatches must be an even divisor of ntest, increase if you run out of memory
if ntest > 1000
  nbatches = 50
  else
  nbatches = 5
end

nel = ntest ÷ nbatches
batches = [nel*(i-1)+1:nel*i for i = 1:nbatches]

ypred = zeros(UInt8, ntest)
# classify
for i=1:nbatches
  dist = sqdistance(Xtest[batches[i],:], Xtrain, XtestSOS[batches[i]], XtrainSOS)
  for j = 1:length(batches[i])
    closest = indmin(dist[j,:])
    ypred[batches[i][j]] = ytrain[closest]
  end
end

error_rate = mean(ypred .!= ytest)

println("Error Rate : ", 100 * error_rate)


### Plot example
using Plots
pyplot()

# line plot example random data
plot(10*rand(10,1), label="accuracy")

# image plot
img = flipdim(train_images[:,:,3], 1)  # plot the third image
heatmap(1:28, 1:28, img, fillcolor = :grays, legend = false)
Plots.gui()
