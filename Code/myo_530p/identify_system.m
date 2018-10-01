function [a,b]=identify_system(u,y,na,nb)

%lenght of the SISO
m=length(y);
%% init variables for calculations
theta=zeros(1,na+nb)'; % create a zero vector for the coefficients a and b, 2 for a 2 for b
alpha=1e4; %%init factor
residual=zeros(1,m);
error_v=zeros(1,m);
P=alpha*eye(na+nb); % Covariance Matrix
lambda=1; % Forgetting Factor
lambda_inv=1/lambda; % inverse Forgetting Factor
error=0;
error_n=1;
%% for errors and parameters graphs
coeffs_historial=zeros(na+nb,m);
coeffs_historial_error=zeros(na+nb,m);
%% algorithm
for k=(na+nb):m%%sweeping out y
    %taking the new seeds for the coefficients estimation or observations,
    %2 samples behind
    xt=[];
    for order=1:na,
        xt=[xt -y(k-order)];
    end
    for order=1:nb,
        xt=[xt u(k-order)];
    end
    %% RLS calculations
    x=xt';%x from xT
    %calculating P cvariance matrix
    P=lambda_inv*(P-(P*x*xt*P)/(lambda+xt*P*x));
    %taking the covariance matrix calculate and update the weights (Thetha, which are A(t), and B(t) coeffiecients)
    theta_prev=theta;
    theta=theta-P*x*(xt*theta-y(k));
               %____
                 %|
                 %.-> K(t+1)=P*x=P(t+1)*x(t+1)

    %% save the progress of each coefficients to see the convergence, and
    %error.
    for order=1:na,
        coeffs_historial(order,k)=theta(order);
        coeffs_historial_error(order,k)=abs(coeffs_historial(order,k)-theta_prev(order));
    end
    for order=1:nb,
        coeffs_historial(order+na,k)=theta(order+na);
        coeffs_historial_error(order+na,k)=abs(coeffs_historial(order+na,k)-theta_prev(order+na));
    end

 

end


%taking out the coeficcients
a=[];
b=[];

for order=1:na,
   a=[a theta(order,1)];
end
for order=1:nb,
   b=[b theta(na+order,1)];
end

a= [1 a];
return
