function [thetaest,P] = rls(y,phi,thetaest,P,lambda)
% Basic Recursive Least-Squares (RLS) parameter update
% Inputs: yk,?k, ?: current output & past input/outputs column vector & forgetting factor
 % Input/Outputs: ?,P: parameter estimates & covariance matrix
if nargin < 5
lambda = 0.995; % Set default forgetting factor, ?
end % if

K=P*phi/(lambda + phi'*P*phi); % Gain K, Eqn. 6.57.
P=(P-(P*phi*phi'*P)/(lambda+phi'*P*phi))/lambda;% Covariance update, P, Eqn. 6.58.
thetaest = thetaest + K*(y - phi'*thetaest);% ?N+1 = ?N +KN+1 ?yN+1 ? ?T
return % end rls.m