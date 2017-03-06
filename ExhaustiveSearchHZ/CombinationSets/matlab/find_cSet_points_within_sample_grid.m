% find_cSet_points_within_sample_grid.m
% Finds the global indices points within 
% the an sub-square of dimension n*n.
% The global indices correspond to the main
% grid of dimension n^2=201^2


fprintf('%s\n',repmat('=',1,52));

n=57; p=72;

% make first subgrid/region row
a(1) = p+1 + (p+1)*(n+2*p); % remember: n+2*p = main_n = n201
b(1) = a(1) + (n-1);

% fill in:
T(1,:) = [ a(1) b(1) ];
s(1) = { T(1,1) : T(1,2) };

% iterate for each region row, global indexing top to bottom
for ii = 2 : n

	a(ii) = b(ii-1)+2*p+1; 
	b(ii) = a(ii) + (n-1);

	% fill in:
	T(ii,:) = [a(ii) b(ii)];
	s(ii) = { T(ii,1) : T(ii,2) };

end

% show first five rows
for ii = 1 : 5
	ls = length(s{ii});
	fprintf('length of s: %d\n',ls)
	for jj = 1 : ls
		if(jj>ls/2 && jj<ls/2+1)
			fprintf('\n')
		end
		fprintf(' %d',s{ii}(jj))
	end
	fprintf('\n\n')
end

% assemble all point indices
v = horzcat(s{:});

% test total length of index vector
fprintf('total length of N: %d\n', length(v));
fprintf('should be: %d\n', n^2);

fprintf('%s\n',repmat('=',1,52));

main_n=201;
coord = global_idx_to_coord(v,main_n);
plot_grid_subset_within_global_grid(coord,main_n,n,p);

% convert point indices into grid coordinates
function coord = global_idx_to_coord(v,main_n)

	coord(:,2) = floor(v./main_n); % y
	coord(:,1) = v' - coord(:,2).*main_n; % x

end


% plot grid coordinates within global point grid
function plot_grid_subset_within_global_grid(coord,main_n,n,p)

clf
hold on;
box on;

% for ii = 1 : size(ncells,1)

	C = repmat(1,size(coord,1),size(coord,1));
	pcolor(coord(:,1), coord(:,2),C);

% end

grid on;
grid minor;
axis square;


colormap(jet(size(coord,1)))
colorbar

% close up to selection
% s = 1;
% axis([p+1-s n+p+s p+1-s n+p+s])
% set(gca,'XTick',p+1-s:1:n+p+s)
% set(gca,'YTick',p+1-s:1:n+p+s)

% medium close up
% s = 10;
% axis([p+1-s n+p+s p+1-s n+p+s])
% set(gca,'XTick',p+1-s:5:n+p+s)
% set(gca,'YTick',p+1-s:5:n+p+s)

full grid
axis([1 main_n 1 main_n]) 
set(gca,'XTick',1:20:201)
set(gca,'YTick',1:20:201)

end







