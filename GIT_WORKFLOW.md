# Git Workflow for C++ Mastery

## Repository Setup ✅
**Local Git Config**: Separate from your global Git settings
- **Name**: C++ Mastery Student  
- **Email**: cpp.mastery@learner.local
- **Scope**: Only applies to this repository

```bash
cd /home/eshdiar/cpp/cpp-mastery
git config user.name    # Shows: C++ Mastery Student
git config user.email   # Shows: cpp.mastery@learner.local
```

## Change Local Config (if needed)
```bash
cd /home/eshdiar/cpp/cpp-mastery
git config --local user.name "Your Learning Name"
git config --local user.email "your.learning@email.com"
```

## Branch Structure
- **main** - Stable completed work
- **week-1** - Week 1 development
- **week-2** - Week 2 development  
- **week-3** - Week 3 development
- **week-4** - Week 4 development
- **feature/project-name** - Individual project branches

## Daily Workflow

### Start New Week
```bash
git checkout main
git pull origin main  # If using remote
git checkout -b week-1  # Create week branch
```

### Work on Projects
```bash
# Create feature branch for specific project
git checkout -b feature/calculator-project

# Work on your code...
# Add files
git add .
git commit -m "feat: implement basic calculator functionality"

# More commits...
git commit -m "feat: add expression parser"
git commit -m "test: add unit tests for calculator"
git commit -m "docs: update calculator README"
```

### Complete Project
```bash
# Merge back to week branch
git checkout week-1
git merge feature/calculator-project
git branch -d feature/calculator-project  # Delete feature branch
```

### Complete Week
```bash
# Merge week to main
git checkout main
git merge week-1
git tag week-1-complete
```

## Commit Message Convention
```
type(scope): description

Types:
- feat: New feature
- fix: Bug fix
- docs: Documentation
- test: Tests
- refactor: Code refactoring
- perf: Performance improvement
- style: Code style changes

Examples:
feat(calculator): implement expression parsing
fix(memory): resolve memory leak in smart pointer
test(banking): add unit tests for account class
docs(week-1): update project requirements
```

## Useful Git Aliases (Already Configured)
```bash
git st          # git status
git co          # git checkout
git br          # git branch
git ci          # git commit
git unstage     # git reset HEAD --
git last        # git log -1 HEAD
git progress    # git log --oneline --graph --decorate
git week        # git log --oneline --grep="Week"
```

## Progress Tracking Integration
```bash
# After completing a project
python3 update_progress.py complete project "Calculator"
git add progress_state.json
git commit -m "progress: complete calculator project"

# After completing theory
python3 update_progress.py complete theory "basics.md"
git add progress_state.json  
git commit -m "progress: complete basics theory"
```

## Remote Repository Setup (Optional)
```bash
# Add remote repository
git remote add origin https://github.com/yourusername/cpp-mastery.git

# Push to remote
git push -u origin main

# Push all branches
git push --all origin

# Push tags
git push --tags origin
```

## Backup Strategy
```bash
# Create backup branch before major changes
git checkout -b backup-$(date +%Y%m%d)
git checkout main

# Archive completed weeks
git checkout -b archive/week-1 week-1
```

## View Progress
```bash
# See all commits
git progress

# See week-specific commits  
git week

# See project commits
git log --oneline --grep="feat"

# See current branch and status
git st
```

## Troubleshooting

### Undo Last Commit (Keep Changes)
```bash
git reset --soft HEAD~1
```

### Undo Last Commit (Discard Changes)
```bash
git reset --hard HEAD~1
```

### Switch Between Weeks
```bash
git stash          # Save current work
git checkout week-2
git stash pop      # Restore work
```

### Clean Working Directory
```bash
git clean -fd      # Remove untracked files
git reset --hard   # Reset to last commit
```

## Integration with Progress Tracker
The Git workflow integrates with your progress tracker:

1. **Commit after each completed task**
2. **Update progress tracker**
3. **Tag major milestones**
4. **Use branches for organization**
5. **Maintain clean commit history**

This ensures your learning progress is both tracked and version-controlled!
