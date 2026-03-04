function stegdir_decode(inputPath, outputPath)
%#codegen

    arguments
        inputPath       (1, 1)  string
        outputPath      (1, 1)  string
    end

    if isunix
        dirList = string(splitlines(ls(inputPath)));
        dirList = dirList(1:end-1);
    else
        dirList = ls(inputPath);
    end

    fout = fopen(outputPath, "wb");
    for iDir = 1:size(dirList, 1)
        blockData = textscan(dirList(iDir, :), "%d_%s");
        blockData_decoded = base64Decode(blockData{2}{1}, true);
        fwrite(fout, blockData_decoded, "uint8");
    end

    fclose(fout);
end