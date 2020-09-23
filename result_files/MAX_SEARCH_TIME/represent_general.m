filepath = 'MAX_SEARCH_TIME.csv';
variable_x = 19;

location_detections = 20;
location_fp = 21;
location_real_detections = 22;
location_num_attacks = 4;


%Find the text associated to the variable to be represented
fileID = fopen('../../stats_headers', 'r');
headers_prov = textscan(fileID, '%s %*d8 %*[^\n]', 'Delimiter', ',');
headers = headers_prov{1};
fclose(fileID);

header = headers(variable_x);

Data = csvread(filepath);

[Y,I] = sort(Data(:,variable_x));
Data_ordered = Data(I,:);

x = Data_ordered(:,variable_x)';
detections = Data(:, location_detections)';
fp = Data(:, location_fp)';
real_detections = Data(:, location_real_detections)';
num_attacks = Data(:, location_num_attacks)';

rate_fp = fp./detections;
rate_real_detections = real_detections./num_attacks;

plot(x, rate_fp,'b-o', x, rate_real_detections, 'r-x')
axis([-inf inf 0 1])
legend('False Positives','Real Detections')
x_label = xlabel(header);
set(x_label, 'interpreter', 'none');



