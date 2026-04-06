classdef FunctionalTests < matlab.unittest.TestCase

    properties (Constant)
        nRandomisedTestIterations = 1024;
        maxBytesRandomisedTest = 1024;
    end
    
    properties
        testTempDir
    end

    properties (TestParameter)
        % Use function handles to bind C wrappers through TestParameters
        Implementation = struct( ...
            'matlab', struct('encode', @stegdir_encode,           'decode', @stegdir_decode), ...
            'c',      struct('encode', @FunctionalTests.cEncode,  'decode', @FunctionalTests.cDecode) ...
            )
    end

    %% Test class methods

    methods (TestMethodSetup)
        function createTempDir(testCase)
            testCase.testTempDir = tempname();
            mkdir(testCase.testTempDir);
        end
    end

    methods (TestMethodTeardown)
        function deleteTempDir(testCase)
            if isfolder(testCase.testTempDir)
                rmdir(testCase.testTempDir, 's');
            end
        end
    end


    methods (Test)

        function randomEncodeAndDecode(testCase, Implementation)
            for i = 1:testCase.nRandomisedTestIterations
                nBytes  = randi([1, testCase.maxBytesRandomisedTest]);
                payload = uint8(randi([0 255], nBytes, 1));
                testCase.encodeAndDecode(Implementation, payload, i);
            end
        end
        
    end
    
    methods (Access = private)
 
        function encodeAndDecode(testCase, impl, inputData, iteration)
 
            inputFile     = fullfile(testCase.testTempDir, "testFile_"   + num2str(iteration) + "_in.bin");
            outputFile    = fullfile(testCase.testTempDir, "testFile_"   + num2str(iteration) + "_out.bin");
            encodedFolder = fullfile(testCase.testTempDir, "testDir_"   + num2str(iteration));
 
            fout = fopen(inputFile, "wb");
            fwrite(fout, inputData, "uint8");
            fclose(fout);
 
            impl.encode(inputFile, encodedFolder);
            impl.decode(encodedFolder, outputFile);
 
            fin         = fopen(outputFile, "rb");
            decodedData = uint8(fread(fin, "uint8"));
            fclose(fin);
 
            testCase.assertEqual(decodedData, inputData, "Data mismatch");
        end
    end

    %  Wrapper methods to C binary
    methods (Static, Access = private)

        function cEncode(inputFile, encodedFolder)
            returnCode = system("../stegdir encode " + inputFile + " " + encodedFolder);
            assert(returnCode == 0, "stegdir encode exited with code %d.", returnCode);
        end
    
        function cDecode(encodedFolder, outputFile)
            returnCode = system("../stegdir decode " + encodedFolder + " " + outputFile);
            assert(returnCode == 0, "stegdir decode exited with code %d.", returnCode);
        end
 
    end

end