import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Random;
import java.util.*; 

class Board
{
	public int[][] init_board;
	public int[][] act_board;
	public Pair zerro;
	public Pair[] neighbours;
	public Pair[] positions;

	public void generate_board()
	{
		for(int i = 0; i < 100; i++)
			{
				this.random_move();
			}
	}
		
	public Board()
	{
		
		init_board = new int[4][4];
		act_board = new int[4][4];
		positions = new Pair[16];

		int c = 0;
		for(int i = 0;i < 4;i ++)
			for(int j = 0; j < 4;j ++)
			{
				
				c += 1;
				if(c < 16)
				{
					positions[c] = new Pair(j,i);
					init_board[i][j] = c;
					act_board[i][j] = c;
				}
				else
				{
					positions[0] = new Pair(j,i);
					init_board[i][j] = 0;
					act_board[i][j] = 0;
				}
			}
		neighbours = new Pair[4];
		neighbours[0] = new Pair(-1,0);
		neighbours[1] = new Pair(1,0);
		neighbours[2] = new Pair(0,-1);
		neighbours[3] = new Pair(0,1);			

		zerro = new Pair(3,3);
	}

	public Pair[] find_moves()
	{
		Pair result[] = new Pair[4];
		for (int i = 0; i < 4 ;i ++)
		{
			result[i] = null;
		}

		int x = zerro.x;
		int y = zerro.y;

			
		int n = 0;

		for (int i = 0 ;i < 4; i ++)
		{
			int new_x = x + this.neighbours[i].x;
			int new_y = y + this.neighbours[i].y;
			if (new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4 
				&& x >= 0 && x < 4 && y >= 0 && y < 4)
			{
				result[n] = new Pair(new_x,new_y);
				n += 1;
			}
		}

		return result;
	}

	public Pair make_move(int x, int y)
	{	
		Pair trans = new Pair(-1,-1);
		Pair result = null;

		for(int i = 0; i < 4; i ++)
		{
			int new_x = x + this.neighbours[i].x;
			int new_y = y + this.neighbours[i].y;
			if (new_x >= 0 && new_x < 4 && new_y >= 0 && new_y < 4 
				&& x >= 0 && x < 4 && y >= 0 && y < 4)
			{
				if (act_board[new_y][new_x] == 0)
					trans.set_val(new_x,new_y);
			}
 		}
 		if (trans.x != -1 && trans.y != -1)
 		{
 			int to_change = act_board[trans.y][trans.x];
 			act_board[trans.y][trans.x] = act_board[y][x];
 			zerro.set_val(x,y);
 			act_board[y][x] = to_change;
 			result = trans;
 		}
 		
 		return result;
	}

	public int count_dist(int val, int x, int y)
	{
		int good_x = positions[val].x;
		int good_y = positions[val].y;
		return Math.abs(x - good_x) + Math.abs(y - good_y);
	}

	public int heuristic(int x, int y, Board b)
	{
		int result = 0;

		Board new_state = new Board();
		for(int i = 0;i < 4;i ++)
			for(int j = 0; j < 4;j ++)
			{
				new_state.act_board[i][j] = b.act_board[i][j];
			}
		Pair tmppair = new Pair(b.zerro.x,b.zerro.y);
		new_state.zerro = tmppair;
		new_state.make_move(x,y);
		
		for(int i = 0;i < 4;i ++)
			for(int j = 0; j < 4;j ++)
			{
				int new_y = i;
				int new_x = j;
				int val = new_state.act_board[i][j];
				result += count_dist(val,new_x,new_y);
			}
		return result;
	}

	public void random_move()
	{
		Pair moves[];
		moves = this.find_moves();
		int cnt_moves = 0;
		int max_value = 0;
		Pair best_move = null;
		for(int i = 0; i < 4; i ++)
		{
			if(moves[i] != null)
			{
				cnt_moves += 1;
				int value = heuristic(moves[i].x,moves[i].y,this);
				if (value >= max_value)
				{
					if (value == max_value)
					{
						int rand = new Random().nextInt(101);
						if (rand >= 50)
							best_move = moves[i];
					}
					else
						best_move = moves[i];
					max_value = value;
				}
			}
		}
		//System.out.println(max_value);
		//int randomMove = new Random().nextInt(cnt_moves);
		//Pair move = moves[randomMove];
		make_move(best_move.x,best_move.y);
	}
		
	public void draw()
	{
		for(int i = 0;i < 4;i ++)
		{
			for(int j = 0; j < 4;j ++)
			{
				System.out.print(this.act_board[i][j] + " ");
			}
			System.out.println("");
		}

	}

	public Boolean terminal()
	{
		for(int i = 0; i < 4; i ++)
			for(int j = 0; j < 4; j ++)
			{
				if (act_board[i][j] != init_board[i][j])
					return false;
			}
		return true;
	}
		
	class Board_info
	{
		public int[][] board;
		public Board_info(int[][] x)
		{
			board = new int[4][4];
		
		for(int i = 0;i < 4;i ++)
			for(int j = 0; j < 4;j ++)
			{
				this.board[i][j] = x[i][j];
			}
		}

		@Override
		public int hashCode()
		{
			int hash = java.util.Arrays.deepHashCode( board );
			return hash;
		}
		@Override
		public boolean equals(Object obj)
		{
			if (this == obj)
		        return true;
		    if (obj == null)
		        return false;
		    if (getClass() != obj.getClass())
		        return false;
			Board_info other_board = (Board_info) obj;
			for(int i = 0;i < 4;i ++)
			{
				for(int j = 0; j < 4;j ++)
				{
					if(this.board[i][j] != other_board.board[i][j])
						return false;
				}
			}
			return true;
		}
	}

	class State implements Comparable <State>
	{
		public Integer value;
		public Pair move;
		public int cnt_moves;
		public State before;
		public Board board;
		public State(int v, int c, Pair m, Board b,State b4)
		{
			this.board = b;
			this.cnt_moves = c;
			this.before = b4;
			this.value = v;
			this.move = m;
		}
		public void set_val(int v, int c, Pair m, Board b,State b4)
		{
			this.board = b;
			this.cnt_moves = c;
			this.before = b4;
			this.value = v;
			this.move = m;
		}
		@Override
		public int compareTo(State other)
		{
			return this.value.compareTo(other.value);
		}

	}

	public Pair[] moves_queue(State s)
	{
		State tmps = s;
		Pair result[] = new Pair[tmps.cnt_moves];
		int i = tmps.cnt_moves - 1;
		while(tmps.before != null)
		{	
			result[i] = tmps.move;
			i -= 1;
			tmps = tmps.before;
		}
		return result;
	}
	
	public Pair[] BFS()
	{
		
		if(this.terminal())
		{
			return null;
		}
		PriorityQueue<State> pQueue = new PriorityQueue<State>();
		State beg_state = new State(0,0,null,this,null);
		pQueue.add(beg_state);

		Set<Board_info> states = new HashSet<Board_info>();
		Board_info beg_board = new Board_info(this.act_board);
		states.add(beg_board);
		
		while (pQueue.size() > 0)
		{
			State state = pQueue.poll();
			int cur_val = state.value;
			Board cur_board = state.board;
			int cur_cnt = state.cnt_moves;

			if(cur_cnt > 34) //cutoff to make game faster
				return null;

			if(cur_board.terminal())
			{
				Pair result[];
				result = moves_queue(state);
				return result;
			}

			Pair moves[];
			moves = cur_board.find_moves();

			for(int k = 0; k < 4; k ++)
			{
				if(moves[k] != null)
				{
					int new_value = heuristic(moves[k].x,moves[k].y,cur_board) + cur_cnt;
					int new_cnt = cur_cnt + 1;
					Board new_board = new Board();
					Pair new_move = moves[k];
					for(int i = 0;i < 4;i ++)
						for(int j = 0; j < 4;j ++)
						{
							new_board.act_board[i][j] = cur_board.act_board[i][j];
						}
					new_board.make_move(new_move.x,new_move.y);

					Board_info concr_board = new Board_info(new_board.act_board);
					if (! states.contains(concr_board))
					{
						State new_state = new State(new_value,new_cnt,new_move,new_board,state);
						states.add(concr_board);
						pQueue.add(new_state);
					}
				}
			}
		}

		return null;
	}
}