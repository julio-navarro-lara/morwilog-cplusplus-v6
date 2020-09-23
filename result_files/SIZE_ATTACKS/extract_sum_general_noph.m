filepath = 'results_extracted_noph.csv';

Data = csvread('../../stats_noph.csv');

% fileID = fopen('../stats_headers', 'r');
% text = textscan(fileID, '%s %d8 %*[^\n]', 'Delimiter', ',');
% fclose(fileID);

% Calculate the average of the lines 

data_mean = mean(Data);

dlmwrite(filepath, data_mean, 'delimiter',',','-append');