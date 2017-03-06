

four_points_per_grid = .25;
n_points_in_50_cell_grid_region = size(0:four_points_per_grid:50,2);

fprintf('four_points_per_grid: %3.2f\n', four_points_per_grid);
fprintf('n_points_in_50_cell_grid_region: %4.0f\n', n_points_in_50_cell_grid_region);


lb = 6;
ub = 55;
% c = [ 0 2.^(0:8) ]
c = 2 .* (0:10)

ncells = [
lb+c(1) ub-c(1)
lb+c(2) ub-c(2)
lb+c(3) ub-c(3)
lb+c(4) ub-c(4)
lb+c(5) ub-c(5)
lb+c(6) ub-c(6)
lb+c(7) ub-c(7)
lb+c(8) ub-c(8)
lb+c(9) ub-c(9)
lb+c(10) ub-c(10)
]

regions = {};
P = {};
for ii = 1 : size(ncells,1)
	regions(ii) = { ncells(ii,1) : ncells(ii,2) };
	before_region(ii) = { lb : ncells(ii,1) - 1 };
	after_region(ii) = { ncells(ii,2) + 1 : ub };
	total_area(ii) = { lb : ub };

	ncells_in_region(ii) = size(regions{ii},2);
	ncells_before_region(ii) = size(before_region{ii},2);
	ncells_after_region(ii) = size(after_region{ii},2);
	ncells_total_area(ii) = size(total_area{ii},2);

	n_points_in_x_cell_grid_region(ii) = ...
	size(0:four_points_per_grid:ncells_in_region(ii),2);
	
	n_points_after_in_x_cell_grid_region(ii) = ...
	size(0.25:four_points_per_grid:ncells_after_region(ii),2);

	n_points_before_in_x_cell_grid_region(ii) = ...
	size(0:four_points_per_grid:ncells_before_region(ii)-.25,2);

	n_points_total_area(ii) = ...
	size(0:four_points_per_grid:ncells_total_area(ii),2);

	[X Y] = meshgrid(regions{ii},regions{ii});
	PX(ii) = { X };
	PY(ii) = { Y };
	PZ(ii) = { repmat(ii,size(X)) };
end


fprintf('ncells_in_region: %3.0f\n', ncells_in_region);
fprintf('ncells_before_region: %3.0f\n', ncells_before_region);
fprintf('ncells_after_region: %3.0f\n', ncells_after_region);

fprintf('\n');
fprintf('n_points_in_x_cell_grid_region: %3.0f\n', ...
	n_points_in_x_cell_grid_region);
fprintf('n_points_before_in_x_cell_grid_region: %3.0f\n', ...
	n_points_before_in_x_cell_grid_region);
fprintf('n_points_after_in_x_cell_grid_region: %3.0f\n', ...
	n_points_after_in_x_cell_grid_region);

fprintf('test_total_n_points (sum) : %3.0f\n', ...
	n_points_in_x_cell_grid_region + ...
	n_points_before_in_x_cell_grid_region + ...
	n_points_after_in_x_cell_grid_region - ...
	n_points_total_area);

clf
hold on;
box on;
grid minor;
axis square;

clr = {
[     0         0    0.6667]
[     0         0    1.0000]
[     0    0.3333    1.0000]
[     0    0.6667    1.0000]
[     0    1.0000    1.0000]
[0.3333    1.0000    0.6667]
[0.6667    1.0000    0.3333]
[1.0000    1.0000         0]
[1.0000    0.6667         0]
[1.0000    0.3333         0]};


for ii = 1 : size(ncells,1)

	% pcolor(PX{ii}, PY{ii}, PZ{ii});
	mesh(PX{ii}-.5, PY{ii}-.5, PZ{ii});

	% scatter3(PX{ii}(:), PY{ii}(:), PZ{ii}(:), 4, clr{ii}, 'filled');
	% scatter3(PX{ii}(:)-.5, PY{ii}(:)-.5, PZ{ii}(:), filled');


end

colormap(jet(size(ncells,1)))
colorbar
axis([1 60 1 60 0 1]) 

cmap = colormap

    %      0         0    0.6667
    %      0         0    1.0000
    %      0    0.3333    1.0000
    %      0    0.6667    1.0000
    %      0    1.0000    1.0000
    % 0.3333    1.0000    0.6667
    % 0.6667    1.0000    0.3333
    % 1.0000    1.0000         0
    % 1.0000    0.6667         0
    % 1.0000    0.3333         0