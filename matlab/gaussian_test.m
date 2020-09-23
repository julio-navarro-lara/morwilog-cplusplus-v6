min_ph = 200;
a_delta = 500;
a_evap = 50;
initial_ph = 1000;
b = initial_ph;
c = 1000;
evap_rate = 0.02;

increment_static = 110;


% x = [min_ph:1:5000];
% 
% delta = a_delta*exp(-((x-initial_ph).^2)/(2*c^2));
% %evap = a_evap*exp(-((x-initial_ph).^2)/(2*c^2));
% evap = x*evap_rate;
% 
% plot(x,delta,x,evap);


%pause;


size_of_simulation = 20;

ph_o = initial_ph;
result_plus = zeros(1,size_of_simulation);
result_minus = zeros(1,size_of_simulation);
result_plus(1) = ph_o;
result_minus(1) = ph_o;

result_plus_old = zeros(1,size_of_simulation);
result_plus_old = ph_o;

for n=2:length(result_plus)
   result_plus(n) = (1-evap_rate)*result_plus(n-1)+a_delta*exp(-((result_plus(n-1)-b)^2)/(2*c^2));
   result_minus(n) = (1-evap_rate)*result_minus(n-1)-a_delta*exp(-((result_minus(n-1)-b)^2)/(2*c^2));

   %result_plus(n) = result_plus(n-1)-a_evap*exp(-((result_plus(n-1)-b)^2)/(2*c^2))+a_delta*exp(-((result_plus(n-1)-b)^2)/(2*c^2));
   result_plus_old(n) = (1-evap_rate)*result_plus_old(n-1)+increment_static;
   %result_minus(n) = result_minus(n-1)-a_evap*exp(-((result_minus(n-1)-b)^2)/(2*c^2))-a_delta*exp(-((result_minus(n-1)-b)^2)/(2*c^2));
   
   if result_minus(n)<min_ph
       result_minus(n) = min_ph;
   end
end

% for n=(length(result_plus)/2):length(result_plus)
%     %result_plus(n) = (1-evap_rate)*result_plus(n-1)-a_delta*exp(-((result_plus(n-1)-b)^2)/(2*c^2));
%     %result_minus(n) = (1-evap_rate)*result_minus(n-1)+a_delta*exp(-((result_minus(n-1)-b)^2)/(2*c^2));
%     %result_plus(n) = result_plus(n-1)-a_evap*exp(-((result_plus(n-1)-b)^2)/(2*c^2))-a_delta*exp(-((result_plus(n-1)-b)^2)/(2*c^2));
%     %result_minus(n) = result_minus(n-1)-a_evap*exp(-((result_minus(n-1)-b)^2)/(2*c^2))+a_delta*exp(-((result_minus(n-1)-b)^2)/(2*c^2));
%     if result_plus(n)<min_ph
%        result_plus(n) = min_ph;
%    end
% end

figure
plot(1:length(result_plus),result_plus,1:length(result_minus), result_minus,1:length(result_plus_old), result_plus_old);
legend('Inc','Dec','Classic');
pause

C = [1:1000:5000];

figure

result_plus = zeros(length(C),size_of_simulation);
result_plus(:,1) = ph_o;

for m=1:length(C)
    for n=2:length(result_plus)
        result_plus(m,n) = (1-evap_rate)*result_plus(m,n-1)+a_delta*exp(-((result_plus(m,n-1)-b)^2)/(2*C(m)^2));
    end
end

plot(1:length(result_plus), result_plus);
legend('1','2','3','4','5');
pause

ph_level = [0:1:5000];
increment = a_delta*exp(-((ph_level-b).^2)/(2*c^2));
evaporation = evap_rate.*ph_level;
plot(1:length(increment), increment, 1:length(evaporation), evaporation, 1:length(evaporation), increment-evaporation);
legend('Increment','Evaporation','I-E');

pause
close all;