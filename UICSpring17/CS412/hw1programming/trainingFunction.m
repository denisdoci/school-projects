## Copyright (C) 2017 Denis Doci
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} trainingFunction (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Denis Doci <denisdoci@Deniss-MacBook-Pro.local>
## Created: 2017-01-29

function [errorRate] = trainingFunction (trainSize, testSize)
  trainndx = 1:trainSize; 
  testndx =  1:testSize; 
  
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
  % Report
  errorRate = mean(ypred ~= ytest);
endfunction
