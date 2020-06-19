### Future Fidelius Work

-Upgrade the BLAS library. Porting OpenBLAS to SGX would undoubtably give a
speed boost. Another option is eigen3. It is written in C++ and someone has
already had sucess in porting it to SGX. See example
[here](https://github.com/ndokmai/eigen-sgx). It may be easier to get eigen3
working with Fidelius than OpenBLAS. The performance boost from using eigen3 is
unknown at this point. The documentation claims that it is roughly equivalent
to GotoBLAS and Intel Math Kernel Library for single threaded applications.
-Investigate 8 bit quantization for the weights in the connected layers. A
quick read of [this](https://arxiv.org/pdf/1806.08342.pdf) paper seems to
indicate that this approach would be quite easy to implement. A quick
examination of the weights for VGG-16 show that they are in a relatively tight
range should be a good candidate for quantization.
- Revisit Prefetching or reserving a chunk of the Enclave for weights
- Implement bias and activation adding directly in the convolutional layers.
  This may have some impact if we move to smaller memory enclaves.
- Measure the time it takes to move encrypted weights directly from unsecure
  memory into an enclave and decrypt. This is essentially the Occulumency
approach with an added step of decryption. Perhaps using 4 or 8 threads for
weight transfer and decryption would be faster than one hardware unit handling
paging and encryption. 
- Investigate the Intel DNN (Deep Neural Network) Library. This was ported to
  SGX in the last few months and might have some insights for us going forward.
- Implement some way of better reusing memory between layers. For example, the
  current implementation allocates a chunk of memory for the output of each
layer. We could allocate two chunks of memory and alternate use between layers.
This might result in having the memory needed in the enclave more frequently.
- Investigate why models like ResNet don't see a better improvement with
  Fidelius. 
- Compression seems somewhat inefficient in current Fidelius implementation.
  The number of page faults is 1/3 the number of page faults for 16 bit
quantization but the time is only slightly better in most circumstances. This
seems to imply that Fidelius is not decompressing as fast the weights are
coming in. 

### Bookkeeping and Good Software Engineering 

- I need to get the SGX work for Fidelius in the CaprDL github repo. It is
  hosted on my personal github as a private repo as an easy way to share
between the Azure VMs. I would prefer to some method of integrating with the
CaprDL repo that would allow us to download the Fidelius code without any of
the other parts of the repo (Notes etc). I would also like to host the Custom
SGX Driver code in a repo.
- Get JB's multiple y-planes integrated with Fidelius. This should allow us to
  extend Fidelius into smaller memory Enclaves.
- Get the READMEs updated for `SGX Installation on Azure`, `SGX Custom Driver
  Installation`, and `Fidelius Validation on Google Cloud with GPU`. These are
in decent shape but should be polished for future use while this is fresh in 
my mind.
- Remove some crud from the current implementation

### Potential Research Work

- Look into how paging works with SGX on Linux. I think we still have more to
  learn here. Maybe SGX2 will be more widely available soon and open up new
possibilities.
- There seems to be a bunch of research on ways to approximate matrix
  multiplication. For example, [here](https://arxiv.org/pdf/1408.4230v2.pdf) is
one example. I am doubtful about the application to our work but it might be
good to take a look.
- Look for ways to do some of the calculations outside the enclave. I believe
  this would involve homomorphic encryption. Moving some of the calculations
outside the enclave would allow using GPUs.
