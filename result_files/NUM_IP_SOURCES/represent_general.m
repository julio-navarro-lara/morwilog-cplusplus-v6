filepath = 'results_extracted.csv';
filepath_noph = 'results_extracted_noph.csv';
variable_x = 1;

location_detections = 20;
location_fp = 21;
location_real_detections = 22;
location_num_attacks = 4;
location_time_exec = 26;


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
detections = Data_ordered(:, location_detections)';
fp = Data_ordered(:, location_fp)';
real_detections = Data_ordered(:, location_real_detections)';
num_attacks = Data_ordered(:, location_num_attacks)';
time_exec = Data_ordered(:, location_time_exec)';

rate_fp = fp./detections;
rate_real_detections = real_detections./num_attacks;

%Data = csvread(filepath_noph);

[Y,I] = sort(Data(:,variable_x));
Data_ordered = Data(I,:);

x_noph = Data_ordered(:,variable_x)';
detections_noph = Data_ordered(:, location_detections)';
fp_noph = Data_ordered(:, location_fp)';
real_detections_noph = Data_ordered(:, location_real_detections)';
num_attacks_noph = Data_ordered(:, location_num_attacks)';
time_exec_noph = Data_ordered(:, location_time_exec)';

rate_fp_noph = fp_noph./detections_noph;
rate_real_detections_noph = real_detections_noph./num_attacks_noph;

plot(x, rate_fp, 'b-o', x, rate_real_detections, 'r-x')
axis([-Inf Inf 0 1])
legend('False Positives','Real Detections')
x_label = xlabel(header);
set(x_label, 'interpreter', 'none');

hold on

plot(x_noph, rate_fp_noph, 'g-o', x_noph, rate_real_detections_noph, 'm-x')

legend('False Positives','Real Detections','FP Noph','RD Noph')

hold off
pause

plot(rate_fp,rate_real_detections,'b-o')
axis([0 1 0 1])

x_label = xlabel('False positive rate');
y_label = ylabel('Real detection rate');
set(x_label, 'interpreter', 'none');

hold on

plot(rate_fp_noph,rate_real_detections_noph,'r-o')

hold off

pause

plot(x, time_exec, 'b-o', x_noph, time_exec_noph, 'r-x')

pause

csvwrite('roc.csv',[rate_fp', rate_real_detections', x']);
csvwrite('roc_noph.csv',[rate_fp_noph',rate_real_detections_noph', x']);

close all







