classdef FunctionalTests < matlab.unittest.TestCase

    properties
        nRandomisedTestIterations = 4;
        maxBytesRandomisedTest = 1024;
        inputFileName;
        outputFileName;
        encodedFolderName;
    end
    

    methods (Test)

        function randomEncodeAndDecode(testCase)

            for iIteration = 1:testCase.nRandomisedTestIterations

                % Generate random bytes and write to file
                inputData = uint8(randi([0 2^8-1], 1, randi([1 testCase.maxBytesRandomisedTest])))';

                testCase.inputFileName      =   [testCase.inputFileName;        "testFile_"+num2str(iIteration)+"_in.bin"];
                testCase.outputFileName     =   [testCase.outputFileName;       "testFile_"+num2str(iIteration)+"_out.bin"];
                testCase.encodedFolderName  =   [testCase.encodedFolderName;    "test_"+num2str(iIteration)];

                fout = fopen(testCase.inputFileName(iIteration), "wb");
                fwrite(fout, inputData, "uint8");
                fclose(fout);

                stegdir_encode(testCase.inputFileName(iIteration), testCase.encodedFolderName(iIteration));
                stegdir_decode(testCase.encodedFolderName(iIteration), testCase.outputFileName(iIteration));

                fin = fopen(testCase.outputFileName(iIteration), "rb");
                decodedData = uint8(fread(fin, "uint8"));
                fclose(fin);

                % Validate that the decoded data matches the original input data
                testCase.verifyEqual(decodedData, inputData);

            end
        end
        
    end
    
    methods (TestMethodTeardown)
        
        function cleanTestOutputs(testCase)
            for iIteration = 1:testCase.nRandomisedTestIterations
                delete(testCase.inputFileName(iIteration));
                delete(testCase.outputFileName(iIteration));
                rmdir(testCase.encodedFolderName(iIteration), 's');
            end
        end
        
    end

end