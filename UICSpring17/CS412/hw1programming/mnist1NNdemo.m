%% Classify the MNIST digits using a one nearest neighbour classifier and Euclidean distance
%% This file is modified from pmtk3.googlecode.com

load('mnistData');
clear
% set training & testing 
sizes = [100, 200, 500, 1000, 2000, 5000, 10000];
accuracy = [];
foundNonMatch = 0;


for i = sizes
  trainndx = 1:i; 
  testndx =  1:i; 
  ntrain = length(trainndx);
  ntest = length(testndx);
  Xtrain = double(reshape(mnist.train_images(:,:,trainndx),28*28,ntrain)');
  Xtest  = double(reshape(mnist.test_images(:,:,testndx),28*28,ntest)');

  ytrain = (mnist.train_labels(trainndx));
  ytest  = (mnist.test_labels(testndx));

  % Precompute sum of squares term for speed
  XtrainSOS = sum(Xtrain.^2,2);
  XtestSOS  = sum(Xtest.^2,2);

  % fully solution takes too much memory so we will classify in batches
  % nbatches must be an even divisor of ntest, increase if you run out of memory 
  if ntest > 1000
  nbatches = 50;
  else
  nbatches = 5;
  end
  batches = mat2cell(1:ntest,1,(ntest/nbatches)*ones(1,nbatches));
  ypred = zeros(ntest,1);
  % Classify
  for i=1:nbatches    
  dst = sqDistance(Xtest(batches{i},:),Xtrain,XtestSOS(batches{i},:),XtrainSOS);
  [junk,closest] = min(dst,[],2);
  ypred(batches{i}) = ytrain(closest);
  end
  
  errorRate = mean(ypred ~= ytest);
  fprintf('Error Rate: %.2f%%\n',100*errorRate);
  accuracy = [accuracy errorRate];
 endfor
  % Report


%%% Plot example
figure();
% line plot example random data
plot( sizes,accuracy);
ylabel('accuracy');
xlabel('size');

%figure();
% image plot
%imshow(mnist.train_images(:,:,3)); % plot the third image

for k = 1:length(ypred)
  if ypred(k) != ytest(k) && foundNonMatch == 0
    foundNonMatch = 1;
    figure();
    imshow(mnist.train_images(:,:,k));
    figure();
    imshow(mnist.test_images(:,:,k));
  end
end
