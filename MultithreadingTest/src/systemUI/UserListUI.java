package systemUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

import Operation.DataException;
import Operation.Main;
import Users.*;

public class UserListUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	private String[][] cellData;
	private String[] columnNames = {"用户名", "身份"};
	private Administrator user;

	private JLabel listname;
	private DefaultTableModel tableModel;
	public JTable table;
	public JScrollPane scrollPane;
	private JButton changeRole, addUser, delUser, exit; 
	private JPanel select;
	private Font font;

	public UserListUI(Administrator user) {
		this.user = user;
		cellData = new String[Main.users.size()][2];
		cellData = user.InitTable();

		setLayout(new BorderLayout(5, 5));
		font = new Font("宋体", Font.BOLD, 36);

		listname = new JLabel("用户列表",SwingUtilities.CENTER);
		listname.setFont(font);
		this.add(BorderLayout.NORTH, listname);

		tableModel = new DefaultTableModel(cellData, columnNames){
			private static final long serialVersionUID = 1L;
			public boolean isCellEditable(int row, int column) {
				return false;
			}			
		};
		
		font = new Font("宋体", Font.BOLD, 36);
		table = new JTable();
		table.setModel(tableModel);	
		table.setPreferredScrollableViewportSize(new Dimension(1000,500));
		table.getTableHeader().setFont(font);
		table.setFont(font);
		table.setRowHeight(36);//设置行高
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();// 设置table内容居中
		tcr.setHorizontalAlignment(JLabel.CENTER);
		table.setDefaultRenderer(Object.class, tcr);
		table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
		table.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);

		scrollPane = new JScrollPane();
		scrollPane.setViewportView(table);
		this.add(BorderLayout.CENTER, scrollPane);

		changeRole = new JButton("修改权限");
		addUser = new JButton("添加用户");
		delUser = new JButton("删除用户");
		exit = new JButton("返回");
		font = new Font("宋体", Font.PLAIN, 24); 
		changeRole.setFont(font);
		addUser.setFont(font);
		delUser.setFont(font);
		exit.setFont(font);
		select = new JPanel();
		select.add(changeRole);
		select.add(addUser);
		select.add(delUser);
		select.add(exit);

		this.add(select, BorderLayout.SOUTH);
		this.setTitle(user.getName());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.pack();
		this.setVisible(true);
		this.setLocationRelativeTo(null);

		changeRole.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int currentRow = table.getSelectedRow();
				if(currentRow == -1) {
					JOptionPane.showMessageDialog(UserListUI.this, "请先选择一行", "提示", JOptionPane.INFORMATION_MESSAGE);
					return;
				}
				Object object = tableModel.getValueAt(currentRow, 0);
				int col = 1;
				int row = table.getSelectedRow();
				String username = (String)object;
				User changing;
				changing = Main.users.get(username);
				new changeRoleUI(UserListUI.this.user, changing, UserListUI.this, row, col);
			}
		});

		addUser.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new addUserUI(user,UserListUI.this);
			}
		});

		delUser.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int currentRow = table.getSelectedRow();
				if(currentRow == -1) {
					JOptionPane.showMessageDialog(UserListUI.this, "请先选择一行", "提示", JOptionPane.INFORMATION_MESSAGE);
					return;
				}
				Object object = tableModel.getValueAt(currentRow, 0);
				String username = (String)object;
				try {
					user.delUser(username);
					DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
					tableModel.removeRow(currentRow);	// currentRow是要删除的行序号
					JOptionPane.showMessageDialog(UserListUI.this, "删除用户成功！", "提示", JOptionPane.INFORMATION_MESSAGE);

				} catch (DataException e1) {
					JOptionPane.showMessageDialog(UserListUI.this, e1.getString(), "提示", JOptionPane.INFORMATION_MESSAGE);
				}
			}
		});
		exit.addActionListener(this);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == exit) {
			this.dispose();
			new AdministratorUI(user);
		}
	}

	public void addrow(String name, String role) {
		String[] info = new String[2];
		info[1] = role;
		info[0] = name;
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.addRow(info);
	}

	public void changedata(String role, int row, int col) {
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.setValueAt(role, row, col);
	}
}
